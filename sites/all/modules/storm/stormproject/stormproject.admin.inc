<?php
// $Id: stormproject.admin.inc,v 1.9.4.16 2009/04/16 19:20:13 magnity Exp $

/**
 * @file
 */

function stormproject_list() {
  $breadcrumb = array();
  $breadcrumb[] = l(t('Storm'), 'storm');
  drupal_set_breadcrumb($breadcrumb);

  if (array_key_exists('organization_nid', $_GET)) {
    if ($_SESSION['stormproject_list_filter']['organization_nid'] != $_GET['organization_nid']) {
      $_SESSION['stormproject_list_filter']['organization_nid'] = $_GET['organization_nid'];
    }
  }

  $o = drupal_get_form('stormproject_list_filter');

  $i = new stdClass();
  $i->type = 'stormproject';

  $header = array(
    array(
      'data' => ' ',
    ),
    array(
      'data' => t('Organization'),
      'field' => 'spr.organization_title',
      'sort' => 'asc',
    ),
    array(
      'data' => t('Title'),
      'field' => 'n.title',
    ),
    array(
      'data' => t('Status'),
      'field' => 'spr.projectstatus',
    ),
    array(
      'data' => t('Priority'),
      'field' => 'spr.projectpriority',
    ),
    array(
      'data' => storm_icon_add_node($i, $_GET),
      'class' => 'storm_list_operations',
    ),
  );

  $s  = "SELECT n.*, spr.* FROM {node} AS n INNER JOIN {stormproject} AS spr ON n.vid=spr.vid WHERE n.status=1 AND n.type='stormproject'";

  $where = array();
  $args = array();

  if ($_SESSION['stormproject_list_filter']['organization_nid']) {
    $where[] = 'spr.organization_nid=%d';
    $args[] = $_SESSION['stormproject_list_filter']['organization_nid'];
  }
  if ($_SESSION['stormproject_list_filter']['projectcategory'] && $_SESSION['stormproject_list_filter']['projectcategory'] != '-') {
    $where[] = "spr.projectcategory='%s'";
    $args[] = $_SESSION['stormproject_list_filter']['projectcategory'];
  }
  if ($_SESSION['stormproject_list_filter']['projectstatus'] && $_SESSION['stormproject_list_filter']['projectstatus'] != '-') {
    $status = split(',', $_SESSION['stormproject_list_filter']['projectstatus']);
    $v = array();
    foreach ($status as $item) $v[] = '%s';
    $where[] = "spr.projectstatus IN ('". implode("','", $v) ."')";
    foreach ($status as $key => $value) {
      $args[] = $value;
    }
  }
  if ($_SESSION['stormproject_list_filter']['projectpriority'] && $_SESSION['stormproject_list_filter']['projectpriority'] != '-') {
    $where[] = "spr.projectpriority='%s'";
    $args[] = $_SESSION['stormproject_list_filter']['projectpriority'];
  }

  $datebeginfrom = $_SESSION['stormproject_list_filter']['datebeginfrom'];
  if ($datebeginfrom) {
    $datebeginfrom['hour'] = 0;
    $datebeginfrom['minute'] = 0;
    $t = _storm_datetime_to_gmtimestamp($datebeginfrom);
    if ($datebeginfrom['year']>0 && $t>=0) {
      $where[] = 'spr.datebegin>=%d';
      $args[] = $t;
    }
  }

  $datebeginto = $_SESSION['stormproject_list_filter']['datebeginto'];
  if ($datebeginto) {
    $datebeginto['hour'] = 23;
    $datebeginto['minute'] = 59;
    $t = _storm_datetime_to_gmtimestamp($datebeginto);
    if ($datebeginto['year']>0 && $t>=0) {
      $where[] = 'spr.datebegin<=%d';
      $args[] = $t;
    }
  }

  $dateendfrom = $_SESSION['stormproject_list_filter']['dateendfrom'];
  if ($dateendfrom) {
    $dateendfrom['hour'] = 0;
    $dateendfrom['minute'] = 0;
    $t = _storm_datetime_to_gmtimestamp($dateendfrom);
    if ($dateendfrom['year']>0 && $t>=0) {
      $where[] = 'spr.dateend>=%d';
      $args[] = $t;
    }      
  }

  $dateendto = $_SESSION['stormproject_list_filter']['dateendto'];
  if ($dateendto) {
    $dateendto['hour'] = 23;
    $dateendto['minute'] = 59;
    $t = _storm_datetime_to_gmtimestamp($dateendto);
    if ($dateendto['year']>0 && $t>=0) {
      $where[] = 'spr.dateend<=%d';
      $args[] = $t;
    }
  }

  $itemsperpage = $_SESSION['stormproject_list_filter']['itemsperpage'];

  $tablesort = tablesort_sql($header);

  $s = stormproject_access_sql($s, $where);
  $s = db_rewrite_sql($s);
  $r = pager_query($s . $tablesort, $itemsperpage, 0, NULL, $args);

  $projects = array();
  while ($project = db_fetch_object($r)) {
    $projects[] = $project;
  }

  $o .= theme('stormproject_list', $header, $projects);
  $o .= theme('pager', NULL, 10, 0);
  print theme('page', $o);
}

function stormproject_list_filter() {
  $organization_nid = $_SESSION['stormproject_list_filter']['organization_nid'];

  $category_list = stormattribute_attributes_bydomain('project category search');
  $projectcategory = $_SESSION['stormproject_list_filter']['projectcategory'];
  if (!$projectcategory) {
    $projectcategory = $category_list['default'];
    $_SESSION['stormproject_list_filter']['projectcategory'] = $projectcategory;
  }

  $status_list = stormattribute_attributes_bydomain('project status search');
  $projectstatus = $_SESSION['stormproject_list_filter']['projectstatus'];
  if (!$projectstatus) {
    $projectstatus = $status_list['default'];
    $_SESSION['stormproject_list_filter']['projectstatus'] = $projectstatus;
  }

  $priority_list = stormattribute_attributes_bydomain('project priority search');
  $projectpriority = $_SESSION['stormproject_list_filter']['projectpriority'];
  if (!$projectpriority) {
    $projectpriority = $priority_list['default'];
    $_SESSION['stormproject_list_filter']['projectpriority'] = $projectpriority;
  }

  $datebeginfrom = $_SESSION['stormproject_list_filter']['datebeginfrom'];
  $datebeginto = $_SESSION['stormproject_list_filter']['datebeginto'];
  $dateendfrom = $_SESSION['stormproject_list_filter']['dateendfrom'];
  $dateendto = $_SESSION['stormproject_list_filter']['dateendto'];

  $itemsperpage = $_SESSION['stormproject_list_filter']['itemsperpage'];
  if (!$itemsperpage) {
    $itemsperpage = 10;
    $_SESSION['stormproject_list_filter']['itemsperpage'] = 10;
  }

  $form = array();

  $form['filter'] = array(
        '#type' => 'fieldset',
        '#title' => t('Filter'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
  );

  $s = "SELECT n.nid, n.title FROM {node} AS n INNER JOIN {stormorganization} AS sor ON n.vid=sor.vid WHERE n.status=1 AND n.type='stormorganization' ORDER BY n.title ";
  $s = stormorganization_access_sql($s);
  $s = db_rewrite_sql($s);
  $r = db_query($s);

  $organizations = array();
  while ($organization = db_fetch_object($r)) {
    $organizations[$organization->nid] = $organization->title;
  }
  $form['filter']['organization_nid'] = array(
    '#type' => 'select',
    '#title' => t('Organization'),
    '#default_value' => $organization_nid,
    '#options' => array(0 => t('All')) + $organizations,
  );

  $form['filter']['group1'] = array(
    '#type' => 'markup',
    '#theme' => 'storm_form_group',
  );

  $form['filter']['group1']['projectcategory'] = array(
    '#type' => 'select',
    '#title' => t('Category'),
    '#default_value' => $projectcategory,
    '#options' => $category_list['values'],
  );

  $form['filter']['group1']['projectstatus'] = array(
    '#type' => 'select',
    '#title' => t('Status'),
    '#default_value' => $projectstatus,
    '#options' => $status_list['values'],
  );

  $form['filter']['group1']['projectpriority'] = array(
    '#type' => 'select',
    '#title' => t('Priority'),
    '#default_value' => $projectpriority,
    '#options' => $priority_list['values'],
  );

  $form['filter']['group2'] = array(
    '#type' => 'markup',
    '#theme' => 'storm_form_group',
  );

  $form['filter']['group2']['datebeginfrom'] = array(
    '#type' => 'dateext',
    '#withnull' => 'true',
    '#title' => t('Date begin from'),
    '#default_value' => $datebeginfrom,
  );

  $form['filter']['group2']['datebeginto'] = array(
    '#type' => 'dateext',
    '#withnull' => 'true',
    '#title' => t('Date begin to'),
    '#default_value' => $datebeginto,
  );

  $form['filter']['group3'] = array(
    '#type' => 'markup',
    '#theme' => 'storm_form_group',
  );

  $form['filter']['group3']['dateendfrom'] = array(
    '#type' => 'dateext',
    '#withnull' => 'true',
    '#title' => t('Date end from'),
    '#default_value' => $dateendfrom,
  );

  $form['filter']['group3']['dateendto'] = array(
    '#type' => 'dateext',
    '#withnull' => 'true',
    '#title' => t('Date end to'),
    '#default_value' => $dateendto,
  );

  $form['filter']['group4'] = array(
    '#type' => 'markup',
    '#theme' => 'storm_form_group',
  );

  $form['filter']['group4']['itemsperpage'] = array(
    '#type' => 'textfield',
    '#title' => t('Items'),
    '#size' => 10,
    '#default_value' => $itemsperpage,
    '#prefix' => '<div class="container-inline">',
    '#suffix' => '</div>',
  );

  $form['filter']['group4']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Filter'),
    '#submit' => array('stormproject_list_filter_filter'),
  );

  $form['filter']['group4']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset'),
    '#submit' => array('stormproject_list_filter_reset'),
  );

  return $form;
}

function stormproject_list_filter_filter($form, &$form_state) {
  $_SESSION['stormproject_list_filter']['organization_nid'] = $form_state['values']['organization_nid'];
  $_SESSION['stormproject_list_filter']['projectcategory'] = $form_state['values']['projectcategory'];
  $_SESSION['stormproject_list_filter']['projectstatus'] = $form_state['values']['projectstatus'];
  $_SESSION['stormproject_list_filter']['projectpriority'] = $form_state['values']['projectpriority'];
  $_SESSION['stormproject_list_filter']['datebeginfrom'] = $form_state['values']['datebeginfrom'];
  $_SESSION['stormproject_list_filter']['datebeginto'] = $form_state['values']['datebeginto'];
  $_SESSION['stormproject_list_filter']['dateendfrom'] = $form_state['values']['dateendfrom'];
  $_SESSION['stormproject_list_filter']['dateendto'] = $form_state['values']['dateendto'];
  $_SESSION['stormproject_list_filter']['itemsperpage'] = $form_state['values']['itemsperpage'];
}

function stormproject_list_filter_reset($form, &$form_state) {
  unset($_SESSION['stormproject_list_filter']);
}

function _stormproject_organization_projects_js($organization_nid=0) {
  $projects = array();

  if ($organization_nid) {
    $s = "SELECT n.nid, n.title FROM {node} n INNER JOIN {stormproject} AS spr ON n.vid=spr.vid WHERE n.status=1 AND n.type='stormproject' AND spr.organization_nid=%d ORDER BY n.title";
    $s = stormproject_access_sql($s);
    $s = db_rewrite_sql($s);
    $r = db_query($s, $organization_nid);

    while ($item = db_fetch_object($r)) {
      $nid = $item->nid;
      $projects[$nid] = $item->title;
    }
  }
  print drupal_to_js($projects);
  exit();
}

