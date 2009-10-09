<?php
// $Id: stormtimetracking.admin.inc,v 1.9.4.12 2009/02/19 08:00:19 robertogerola Exp $

/**
 * @file
 */

function stormtimetracking_list() {
  $breadcrumb = array();
  $breadcrumb[] = l(t('Storm'), 'storm');
  drupal_set_breadcrumb($breadcrumb);

  if (array_key_exists('organization_nid', $_GET)) {
    if ($_SESSION['stormtimetracking_list_filter']['organization_nid'] != $_GET['organization_nid']) {
      $_SESSION['stormtimetracking_list_filter']['organization_nid'] = $_GET['organization_nid'];
    }
    unset($_SESSION['stormtimetracking_list_filter']['project_nid']);
    unset($_SESSION['stormtimetracking_list_filter']['task_nid']);
    unset($_SESSION['stormtimetracking_list_filter']['ticket_nid']);
  }

  if (array_key_exists('project_nid', $_GET)) {
    if ($_SESSION['stormtimetracking_list_filter']['project_nid'] != $_GET['project_nid']) {
      $_SESSION['stormtimetracking_list_filter']['project_nid'] = $_GET['project_nid'];
    }
    $p = node_load($_GET['project_nid']);
    $_SESSION['stormtimetracking_list_filter']['organization_nid'] = $p->organization_nid;

    unset($_SESSION['stormtimetracking_list_filter']['task_nid']);
    unset($_SESSION['stormtimetracking_list_filter']['ticket_nid']);
  }

  if (array_key_exists('task_nid', $_GET)) {
    if ($_SESSION['stormtimetracking_list_filter']['task_nid'] != $_GET['task_nid']) {
      $_SESSION['stormtimetracking_list_filter']['task_nid'] = $_GET['task_nid'];
    }

    $t = node_load($_GET['task_nid']);
    $_SESSION['stormtimetracking_list_filter']['organization_nid'] = $t->organization_nid;
    $_SESSION['stormtimetracking_list_filter']['project_nid'] = $t->project_nid;
    unset($_SESSION['stormtimetracking_list_filter']['ticket_nid']);
  }

  if (array_key_exists('ticket_nid', $_GET)) {
    if ($_SESSION['stormtimetracking_list_filter']['ticket_nid'] != $_GET['ticket_nid']) {
      $_SESSION['stormtimetracking_list_filter']['ticket_nid'] = $_GET['ticket_nid'];
    }

    $ti = node_load($_GET['ticket_nid']);
    $_SESSION['stormtimetracking_list_filter']['organization_nid'] = $ti->organization_nid;
    $_SESSION['stormtimetracking_list_filter']['project_nid'] = $ti->project_nid;
    $_SESSION['stormtimetracking_list_filter']['task_nid'] = $ti->task_nid;
  }

  $o = drupal_get_form('stormtimetracking_list_filter');

  $i = new stdClass();
  $i->type = 'stormtimetracking';

  $report_attrs = array(
    'onclick' => "storm_popup(this, 'timetracking_list_form_report', 'Timetrackings', 300, 150, 'stormtimetracking_list_form_report', 'l'); return false;",
  );

  $header = array(
    array(
      'data' => t('Organization'),
      'field' => 'stt.organization_title',
    ),
    array(
      'data' => t('Project'),
      'field' => 'stt.project_title',
    ),
    array(
      'data' => t('Title'),
      'field' => 'n.title',
    ),
    array(
      'data' => t('Date'),
      'field' => 'stt.trackingdate',
      'sort' => 'desc',
    ),
    array(
      'data' => t('Duration (h)'),
      'style' => 'text-align: right;'
    ),
    array(
      'data' => storm_icon_l('report', '', t('Reports'), '', array(), $report_attrs) .'&nbsp;'. storm_icon_add_node($i, $_GET),
      'class' => 'storm_list_operations',
    ),
  );

  $s = "SELECT n.*,  stt.* FROM {node} n INNER JOIN {stormtimetracking} stt ON n.vid=stt.vid
  WHERE n.status=1 AND n.type='stormtimetracking' ";

  $s_duration = "SELECT SUM(duration) FROM {stormtimetracking} stt INNER JOIN {node} n ON n.nid=stt.nid WHERE n.status=1 AND n.type='stormtimetracking' ";

  $where = array();
  $args = array();

  if ($_SESSION['stormtimetracking_list_filter']['organization_nid']) {
    $where[] = 'stt.organization_nid=%d';
    $args[] = $_SESSION['stormtimetracking_list_filter']['organization_nid'];
  }
  if ($_SESSION['stormtimetracking_list_filter']['project_nid']) {
    $where[] = 'stt.project_nid=%d';
    $args[] = $_SESSION['stormtimetracking_list_filter']['project_nid'];
  }
  if ($_SESSION['stormtimetracking_list_filter']['task_nid']) {
    $where[] = 'stt.task_nid=%d';
    $args[] = $_SESSION['stormtimetracking_list_filter']['task_nid'];
  }
  if ($_SESSION['stormtimetracking_list_filter']['ticket_nid']) {
    $where[] = 'stt.ticket_nid=%d';
    $args[] = $_SESSION['stormtimetracking_list_filter']['ticket_nid'];
  }
  if ($_SESSION['stormtimetracking_list_filter']['datefrom']) {
    $datefrom = $_SESSION['stormtimetracking_list_filter']['datefrom'];
    $datefrom['hour'] = 0;
    $datefrom['minute'] = 0;
    $where[] = 'stt.trackingdate>=%d';
    $args[] = _storm_datetime_to_gmtimestamp($datefrom);
  }
  if ($_SESSION['stormtimetracking_list_filter']['dateto']) {
    $dateto = $_SESSION['stormtimetracking_list_filter']['dateto'];
    $dateto['hour'] = 23;
    $dateto['minute'] = 59;
    $where[] = 'stt.trackingdate<=%d';
    $args[] = _storm_datetime_to_gmtimestamp($dateto);
  }
  if ($_SESSION['stormtimetracking_list_filter']['billable']!='-' && $_SESSION['stormtimetracking_list_filter']['billable']!= NULL) {
    $where[] = 'stt.billable=%d';
    $args[] = $_SESSION['stormtimetracking_list_filter']['billable'];
  }

  $itemsperpage = $_SESSION['stormtimetracking_list_filter']['itemsperpage'];

  if ($_SESSION['stormtimetracking_list_filter']['user']) {
    $trackinguser = user_load(array('name' => $_SESSION['stormtimetracking_list_filter']['user']));
    if (!$trackinguser->uid) $trackinguser->uid = -1;
    $where[] = 'n.uid=%d';
    $args[] = $trackinguser->uid;
  }

  $s = stormtimetracking_access_sql($s, $where);
  $s = db_rewrite_sql($s);

  $tablesort = tablesort_sql($header);
  $r = pager_query($s . $tablesort, $itemsperpage, 0, NULL, $args);

  $s_duration = stormtimetracking_access_sql($s_duration, $where);
  $s_duration = db_rewrite_sql($s_duration);
  $duration = db_result(db_query($s_duration, $args));

  $_SESSION['stormtimetracking_list_filter']['sql'] = $s . $tablesort;
  $_SESSION['stormtimetracking_list_filter']['args'] = $args;

  $timetrackings = array();
  while ($item = db_fetch_object($r)) {
    $timetrackings[] = $item;
  }

  $o .= theme('stormtimetracking_list', $header, $timetrackings, $duration);
  $o .= theme('pager', NULL, $itemsperpage, 0);
  $o .= drupal_get_form('stormtimetracking_list_form_report');
  print theme('page', $o);
}

function stormtimetracking_list_filter() {
  $organization_nid = $_SESSION['stormtimetracking_list_filter']['organization_nid'];
  $project_nid = $_SESSION['stormtimetracking_list_filter']['project_nid'];
  $task_nid = $_SESSION['stormtimetracking_list_filter']['task_nid'];
  $ticket_nid = $_SESSION['stormtimetracking_list_filter']['ticket_nid'];
  $itemsperpage = $_SESSION['stormtimetracking_list_filter']['itemsperpage'];
  if (!$itemsperpage) {
    $itemsperpage = 10;
    $_SESSION['stormtimetracking_list_filter']['itemsperpage'] = $itemsperpage;
  }

  $datefrom = $_SESSION['stormtimetracking_list_filter']['datefrom'];
  if (!$datefrom) {
    $datefrom = array('day' => 1,
                      'month' => format_date(time(), 'custom', 'n'),
                      'year' => format_date(time(), 'custom', 'Y'),
                      'hour' => 0,
                      'minute' => 0,
                      );
    $_SESSION['stormtimetracking_list_filter']['datefrom'] = $datefrom;
  }

  $dateto = $_SESSION['stormtimetracking_list_filter']['dateto'];
  if (!$dateto) {
    $year = format_date(time(), 'custom', 'Y');
    $month = format_date(time(), 'custom', 'n');
    $day = format_date(mktime(0, 0, 0, ($month + 1), 0, $year), 'custom', 'd');
    $dateto = array('day' => $day,
                     'month' => $month,
                     'year' => $year,
                     'hour' => 23,
                     'minute' => 59,
    );
    $_SESSION['stormtimetracking_list_filter']['dateto'] = $dateto;
  }

  $trackinguser = $_SESSION['stormtimetracking_list_filter']['user'];

  $form = array();

  $form['filter'] = array(
        '#type' => 'fieldset',
        '#title' => t('Filter'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#theme' => 'stormtimetracking_list_filter',
  );

  $form['filter']['group1'] = array(
    '#type' => 'markup',
    '#theme' => 'storm_form_group',
    '#weight' => -20,
  );

  $s = "SELECT n.nid, n.title FROM {node} AS n INNER JOIN {stormorganization} AS sor ON sor.vid=n.vid
  WHERE n.status=1 AND n.type='stormorganization' AND isactive=1 ORDER BY n.title";
  $s = stormorganization_access_sql($s);
  $s = db_rewrite_sql($s);
  $r = db_query($s);
  $organizations = array();
  while ($organization = db_fetch_object($r)) {
    $organizations[$organization->nid] = $organization->title;
  }
  $organizations = array(0 => t('All')) + $organizations;
  $form['filter']['group1']['organization_nid'] = array(
    '#type' => 'select',
    '#title' => t('Organization'),
    '#default_value' => $organization_nid,
    '#options' => $organizations,
    '#attributes' => array('onchange' => "stormticket_organization_project_task_tickets(this, 'edit-project-nid', 'edit-task-nid', 'edit-ticket-nid', true, 'All')"),
  );

  $s = "SELECT n.nid, n.title FROM {node} AS n INNER JOIN {stormproject} AS spr ON spr.vid=n.vid
  WHERE n.status=1 AND spr.organization_nid=%d AND n.type='stormproject' ORDER BY n.title";
  $s = stormproject_access_sql($s);
  $s = db_rewrite_sql($s);
  $r = db_query($s, $organization_nid);
  $projects = array();
  while ($project = db_fetch_object($r)) {
    $projects[$project->nid] = $project->title;
  }
  $projects = array(0 => t('All')) + $projects;
  $form['filter']['group1']['project_nid'] = array(
    '#type' => 'select',
    '#title' => t('Project'),
    '#default_value' => $project_nid,
    '#options' => $projects,
    '#process' => array('storm_dependent_select_process'),
    '#attributes' => array('onchange' => "stormticket_project_task_tickets(this, 'edit-organization-nid', 'edit-task-nid', 'edit-ticket-nid', true, 'All')"),
  );

  $tree = _stormtask_get_tree($project_nid);
  $tasks = _stormtask_plain_tree($tree);
  $tasks = array(0 => t('All')) + $tasks;
  $form['filter']['group1']['task_nid'] = array(
    '#type' => 'select',
    '#title' => t('Task'),
    '#default_value' => $task_nid,
    '#options' => $tasks,
    '#process' => array('storm_dependent_select_process'),
    '#attributes' => array('onchange' => "stormticket_task_tickets(this, 'edit-organization-nid', 'edit-project-nid', 'edit-ticket-nid', true, 'All')"),
  );

  $s = "SELECT n.nid, n.title FROM {node} AS n INNER JOIN {stormticket} AS sti
  ON sti.vid=n.vid WHERE n.status=1 AND n.type='stormticket' AND sti.organization_nid=%d AND sti.project_nid=%d AND sti.task_nid=%d ORDER BY title ";
  $s = stormticket_access_sql($s);
  $s = db_rewrite_sql($s);
  $r = db_query($s, $organization_nid, $project_nid, $task_nid);
  $tickets = array();
  while ($ticket = db_fetch_object($r)) {
    $tickets[$ticket->nid] = $ticket->title;
  }
  $tickets = array(0 => t('All')) + $tickets;
  $form['filter']['group1']['ticket_nid'] = array(
    '#type' => 'select',
    '#title' => t('Ticket'),
    '#default_value' => $ticket_nid,
    '#process' => array('storm_dependent_select_process'),
    '#options' => $tickets,
  );

  $form['filter']['group2'] = array(
    '#type' => 'markup',
    '#theme' => 'storm_form_group',
    '#weight' => -19,
  );

  $form['filter']['group2']['datefrom'] = array(
    '#type' => 'dateext',
    '#title' => t('Date from'),
    '#default_value' => $datefrom,
  );

  $form['filter']['group2']['dateto'] = array(
    '#type' => 'dateext',
    '#title' => t('Date to'),
    '#default_value' => $dateto,
  );

  $form['filter']['group2']['user'] = array(
    '#type' => 'textfield',
    '#title' => t('User'),
    '#size' => 25,
    '#default_value' => $trackinguser,
    '#autocomplete_path' => 'user/autocomplete',
  );

  $form['filter']['billable'] = array(
    '#type' => 'select',
    '#title' => 'Billable',
    '#options' => array('-' => t('all'), '1' => t('billable'), '0' => t('not billable')),
    '#default_value' => $_SESSION['stormtimetracking_list_filter']['billable'],
  );

  $form['filter']['group3'] = array(
    '#type' => 'markup',
    '#theme' => 'storm_form_group',
  );

  $form['filter']['group3']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Filter'),
    '#submit' => array('stormtimetracking_list_filter_filter'),
  );

  $form['filter']['group3']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset'),
    '#submit' => array('stormtimetracking_list_filter_reset'),
  );

  $form['filter']['group3']['itemsperpage'] = array(
    '#type' => 'textfield',
    '#title' => t('Items'),
    '#size' => 10,
    '#default_value' => $itemsperpage,
    '#prefix' => '<div class="container-inline">',
    '#suffix' => '</div>',
  );

  return $form;
}

function stormtimetracking_list_filter_filter($form, &$form_state) {
  $_SESSION['stormtimetracking_list_filter']['organization_nid'] = $form_state['values']['organization_nid'];
  $_SESSION['stormtimetracking_list_filter']['project_nid'] = $form_state['values']['project_nid'];
  $_SESSION['stormtimetracking_list_filter']['task_nid'] = $form_state['values']['task_nid'];
  $_SESSION['stormtimetracking_list_filter']['ticket_nid'] = $form_state['values']['ticket_nid'];
  $_SESSION['stormtimetracking_list_filter']['datefrom'] = $form_state['values']['datefrom'];
  $_SESSION['stormtimetracking_list_filter']['dateto'] = $form_state['values']['dateto'];
  $_SESSION['stormtimetracking_list_filter']['billable'] = $form_state['values']['billable'];
  $_SESSION['stormtimetracking_list_filter']['itemsperpage'] = $form_state['values']['itemsperpage'];
  $_SESSION['stormtimetracking_list_filter']['user'] = $form_state['values']['user'];
}

function stormtimetracking_list_filter_reset($form, &$form_state) {
  unset($_SESSION['stormtimetracking_list_filter']);
}

function stormtimetracking_list_form_report() {
  $form = array();
  $form['#prefix'] = '<div id="stormtimetracking_list_form_report" class="storm_list_form_report">';
  $form['report'] = array(
    '#type' => 'select',
    '#title' => t('Reports'),
    '#options' => theme('stormtimetracking_list_form_report_reports'),
  );

  if (module_exists('locale')) {
    $language_list = language_list();
    $languages = array();
    foreach ($language_list as $key => $lang) {
      $languages[$key] = $lang->name;
    }
    $form['language'] = array(
      '#type' => 'select',
      '#title' => t('Language'),
      '#options' => $languages,
    );
  }
  else {
    $form['language'] = array(
      '#type' => 'hidden',
      '#default_value' => 'en',
    );
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Report'),
  );
  $form['#suffix'] = '</div>';
  return $form;
}

function stormtimetracking_list_form_report_submit($form, &$form_state) {
  $report = $form_state['values']['report'];
  $language = $form_state['values']['language'];
  drupal_goto('storm/timetrackings/report/'. $report .'/'. $language);
}

function stormtimetracking_list_report($report, $language) {
  $timetrackings = array();

  $s = $_SESSION['stormtimetracking_list_filter']['sql'];
  $args = $_SESSION['stormtimetracking_list_filter']['args'];

  $r = db_query($s, $args);
  while ($t = db_fetch_object($r)) {
    $timetracking = node_load($t->nid);
    $timetrackings[] = $timetracking;
  }

  print theme('stormtimetracking_list_report', $report, $language, $timetrackings);
}

