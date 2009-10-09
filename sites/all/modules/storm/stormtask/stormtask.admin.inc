<?php
// $Id: stormtask.admin.inc,v 1.8.4.22 2009/08/20 23:21:03 magnity Exp $

/**
 * @file
 */

function stormtask_tasks($project) {
  $node_invoice = node_load($invoice->nid);
  $breadcrumb = array();
  $breadcrumb[] = l(t('Storm'), 'storm');
  $breadcrumb[] = l(t('Projects'), 'storm/projects');
  $breadcrumb[] = l(t('Project : '. $project->title), 'node/'. $project->nid);
  drupal_set_breadcrumb($breadcrumb);

  $i = new stdClass();
  $i->type = 'stormtask';

  $o = drupal_get_form('stormtask_tasks_filter');

  $params = $_GET;
  $params['organization_nid'] = $project->organization_nid;
  $params['project_nid'] = $project->nid;

  $header = array(
    array(
      'data' => t('Title'),
    ),
    array(
      'data' => t('Category'),
    ),
    array(
      'data' => t('Status'),
    ),
    array(
      'data' => t('Priority'),
    ),
    array(
      'data' => t('Duration'),
      'style' => 'text-align: right;',
    ),
    array(
      'data' => t('Parent'),
    ),
    array(
      'data' => t('Weight'),
    ),
    array(
      'data' => storm_icon_add_node($i, $params),
      'class' => 'storm_list_operations',
    ),
  );

  $where = array();
  $args = array();

  if ($_SESSION['stormtask_tasks_filter']['taskcategory'] && $_SESSION['stormtask_tasks_filter']['taskcategory'] != '-') {
    $category = split(',', $_SESSION['stormtask_tasks_filter']['taskcategory']);
    $v = array();
    foreach ($category as $item) $v[] = '%s';
    $where[] = "sta.taskcategory IN ('". implode("','",$v) ."')";
    foreach ($category as $key => $value) {
      $args[] = $value;
    }
  }
  if ($_SESSION['stormtask_tasks_filter']['taskstatus'] && $_SESSION['stormtask_tasks_filter']['taskstatus'] != '-') {
    $status = split(',', $_SESSION['stormtask_tasks_filter']['taskstatus']);
    $v = array();
    foreach ($status as $item) $v[] = '%s';
    $where[] = "sta.taskstatus IN ('". implode("','",$v) ."')";
    foreach ($status as $key => $value) {
      $args[] = $value;
    }
  }
  if ($_SESSION['stormtask_tasks_filter']['taskpriority'] && $_SESSION['stormtask_tasks_filter']['taskpriority'] != '-') {
    $priority = split(',', $_SESSION['stormtask_tasks_filter']['taskpriority']);
    $v = array();
    foreach ($priority as $item) $v[] = '%s';
    $where[] = "sta.taskpriority IN ('". implode("','",$v) ."')";
    foreach ($priority as $key => $value) {
      $args[] = $value;
    }
  }

  $taskstree = _stormtask_get_tree($project->nid, 0, -1, NULL, $where, $args);
  
  // Display link to jsgantt library only if library is installed.
  $o_gantt ="";
  //$jsgantt_dir = variable_get('stormtask_jsgantt_location', 'sites/all/libraries/jsgantt');
  $jsgantt_dir = drupal_get_path('module', 'stormtask'). '/jsgantt';

  $dispOpt=variable_get('stormtask_jsgantt_options', array());
  if ($dispOpt['ShowStartDate']){$dispOpt['ShowStartDate']=1;}
  if ($dispOpt['ShowEndDate']){$dispOpt['ShowEndDate']=1;}
  if ($dispOpt['ShowDur']){$dispOpt['ShowDur']=1;}

  if(variable_get('stormtask_enable_ganttchart',0) && file_exists($jsgantt_dir .'/jsgantt.js')) {
    drupal_add_js($jsgantt_dir."/jsgantt.js");
    drupal_add_css($jsgantt_dir."/jsgantt.css");

    //version w/o xml file
    $pMile = 0;
    $pRes = "";
    $pComp = 50;
    $pGroup = 0;
    $pParent = 0;
    $pOpen = 1;
    $js = "";
    $pDepend = 0;
    $pParent = 0;
    
    $now = time();
    $one_day = (24 * 60 * 60);
    $pColor_default = variable_get('stormtask_jsgantt_color', '00CCFF');
    $pColor_overdue = variable_get('stormtask_jsgantt_color_overdue', 'FF0D0D');

    foreach($taskstree as $task ) {
      $pID = $task->nid;
      $pName = check_plain($task->title);
      $pCaption = $pName;
      $pLink = base_path()."node/".$task->nid;
      $pStart = date("n/j/Y",$task->datebegin);
      $pEnd = date("n/j/Y",$task->dateend);
      $pColor = variable_get('stormtask_jsgantt_color', '00CCFF'); //$task->taskstatus;
      //$pDepend = $task->parents[0];
      //$pParent = $task->parents[0];

      // theme by task status
      $pColor = variable_get('stormtask_jsgantt_color_' . str_replace(' ', '_', $task->taskstatus), $pColor_default);
      $pComp = 0;
      switch($task->taskstatus) {
        case 'completed':
          $pComp = 100;
          break;
          
        case 'on hold':
          $pComp = 50;
          break;
          
        case 'in progress':
          // percent complete as f($now), end date inclusive
          if ($now > $task->datebegin && $task->dateend > $task->datebegin) {
            $pComp = ($now - $task->datebegin) / ($task->dateend - $task->datebegin + $one_day);
            $pComp = round(100 * $pComp, 2);
          }
          // highlight overdue tasks
          if ($now > $task->dateend) {
            $pColor = $pColor_overdue;
          }
          break;
      }
      
      // show tasks with depth
      if ($task->depth) {
        $pName = str_repeat('--', $task->depth) .' '. $pName;
      }
      
      $js .= "g.AddTaskItem(new JSGantt.TaskItem(".$pID.",'".$pName."','".$pStart."','".$pEnd."','".$pColor."','".$pLink."',".$pMile.",'".$pRes."',".$pComp.",".$pGroup.",".$pParent.",".$pOpen.",".$pDepend.",'".$pCaption."'));\n";
    }

    $o_gantt .= "<div style='position:relative' class='gantt' id='GanttChartDIV'></div>";
    $o_gantt .= "<script>
      // Here is all the html code neccessary to display the chart object
      // Future idea would be to allow XML file name to be passed in and chart tasks built from file.
      var g = new JSGantt.GanttChart('g',document.getElementById('GanttChartDIV'), 'day');
        g.setShowRes(0); // Show/Hide Responsible (0/1)
        g.setShowComp(0); // Show/Hide % Complete(0/1)
        g.setShowDur('".$dispOpt['ShowDur']."'); // Show/Hide Duration (0/1)
        g.setShowStartDate('".$dispOpt['ShowStartDate']."'); // Show/Hide Start Date(0/1)
        g.setShowEndDate('".$dispOpt['ShowEndDate']."'); // Show/Hide End Date(0/1)
        //g.setFormatArr('day','week','month') 
        g.setCaptionType('Resource');  // Set to Show Caption (None,Caption,Resource,Duration,Complete)
      if( g ) {
// Parameters (pID, pName, pStart, pEnd, pColor, pLink, pMile, pRes,  pComp, pGroup, pParent, pOpen)
".$js."

// use the XML file parser 
//    JSGantt.parseXML('http://localhost/services/sites/default/files/project.xml',g)

    g.Draw();
    g.DrawDependencies();
      }
      else
      {
    alert('not defined');
      }
    </script>";
  }
  
  $o .= drupal_get_form('stormtask_tasks_form', $header, $taskstree, $project);
  $o .= $o_gantt;
  return $o;
}

function stormtask_tasks_form($form_id, $header, $tasks, $project) {
  $form = array();

  $form['tasks'] = array(
    '#theme' => 'stormtask_tasks',
  );

  $form['tasks']['header'] = array(
    '#value' => $header,
  );

  $tree = _stormtask_get_tree($project->nid);
  $parent_tasks = _stormtask_plain_tree($tree);

  $params = $_GET;
  $params['project_nid'] = $project->nid;

  foreach ($tasks as $task) {
    $n = new stdClass();
    $n->nid = $task->nid;
    $n->uid = $task->uid;
    $n->type = 'stormtask';

    $form['tasks']['tasks'][$task->nid]['task_depth_'. $task->nid] = array(
      '#value' => $task->depth,
    );

    $form['tasks']['tasks'][$task->nid]['task_description_'. $task->nid] = array(
      '#value' => l($task->stepno .' '. $task->title, 'node/'. $task->nid, array('html' => TRUE)),
    );

    $form['tasks']['tasks'][$task->nid]['task_category_'. $task->nid] = array(
      '#value' => storm_icon('category_'. $task->taskcategory, $task->taskcategory),
    );

    $form['tasks']['tasks'][$task->nid]['task_status_'. $task->nid] = array(
      '#value' => storm_icon('status_'. $task->taskstatus, $task->taskstatus),
    );

    $form['tasks']['tasks'][$task->nid]['task_priority_'. $task->nid] = array(
      '#value' => storm_icon('priority_'. $task->taskpriority, $task->taskpriority),
    );

    $form['tasks']['tasks'][$task->nid]['task_duration_'. $task->nid] = array(
      '#value' => $task->duration,
    );

    $form['tasks']['tasks'][$task->nid]['task_durationunit_'. $task->nid] = array(
      '#type' => 'hidden',
      '#value' => $task->durationunit,
    );

    $form['tasks']['tasks'][$task->nid]['task_parent-nid_'. $task->nid] = array(
      '#type' => 'select',
      '#options' => array(0 => '-') + $parent_tasks,
      '#default_value' => $task->parent_nid,
    );

    $form['tasks']['tasks'][$task->nid]['task_nid_'. $task->nid] = array(
      '#type' => 'hidden',
      '#default_value' => $task->nid,
    );

    $form['tasks']['tasks'][$task->nid]['task_weight_'. $task->nid] = array(
      '#type' => 'weight',
      '#default_value' => $task->weight,
    );

    $v = storm_icon_edit_node($n, $params);
    $v .= '&nbsp;'. storm_icon_delete_node($n, $params);
    $params['parent_nid'] = $task->nid;
    $v .= '&nbsp;'. storm_icon_add_node($n, $params);
    $form['tasks']['tasks'][$task->nid]['task_operations_'. $task->nid] = array(
      '#value' => $v,
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#submit' => array('stormtask_tasks_submit'),
    '#value' => t('Save'),
  );

  return $form;
}

function stormtask_tasks_submit($form, &$form_state) {
  $tasks = array();
  foreach ($form_state['values'] as $key => $value) {
    $ar = explode('_', $key);
    if ($ar[0]=='task') {
      if ($ar[1]=='weight') $tasks[$ar[2]]['weight'] = $value;
      if ($ar[1]=='parent-nid') $tasks[$ar[2]]['parent-nid'] = $value;
    }
  }

  $s = "UPDATE {stormtask} SET weight=%d, parent_nid=%d WHERE nid=%d";  
  foreach ($tasks as $nid=>$values) {
    db_query($s, $values['weight'], $values['parent-nid'], $nid);
  }

  drupal_set_message(t('Tasks saved'));
}

function stormtask_tasks_filter() {
  $category_list = stormattribute_attributes_bydomain('Task category search');
  $taskcategory = $_SESSION['stormtask_tasks_filter']['taskcategory'];
  if (!$taskcategory) {
    $taskcategory = $category_list['default'];
    $_SESSION['stormtask_tasks_filter']['taskcategory'] = $taskcategory;
  }

  $status_list = stormattribute_attributes_bydomain('Task status search');
  $taskstatus = $_SESSION['stormtask_tasks_filter']['taskstatus'];
  if (!$taskstatus) {
    $taskstatus = $status_list['default'];
    $_SESSION['stormtask_tasks_filter']['taskstatus'] = $taskstatus;
  }

  $priority_list = stormattribute_attributes_bydomain('Task priority search');
  $taskpriority = $_SESSION['stormtask_tasks_filter']['taskpriority'];
  if (!$taskpriority) {
    $taskpriority = $priority_list['default'];
    $_SESSION['stormtask_tasks_filter']['taskpriority'] = $taskpriority;
  }

  $form = array();

  $form['filter'] = array(
        '#type' => 'fieldset',
        '#title' => t('Filter'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
  );

  $form['filter']['group1'] = array(
    '#type' => 'markup',
    '#theme' => 'storm_form_group',
  );

  $form['filter']['group1']['taskcategory'] = array(
    '#type' => 'select',
    '#title' => t('Category'),
    '#default_value' => $taskcategory,
    '#options' => $category_list['values'],
  );

  $form['filter']['group1']['taskstatus'] = array(
    '#type' => 'select',
    '#title' => t('Status'),
    '#default_value' => $taskstatus,
    '#options' => $status_list['values'],
  );

  $form['filter']['group1']['taskpriority'] = array(
    '#type' => 'select',
    '#title' => t('Priority'),
    '#default_value' => $taskpriority,
    '#options' => $priority_list['values'],
  );

  $form['filter']['group2'] = array(
    '#type' => 'markup',
    '#theme' => 'storm_form_group',
  );

  $form['filter']['group2']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Filter'),
    '#submit' => array('stormtask_tasks_filter_filter'),
  );

  $form['filter']['group2']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset'),
    '#submit' => array('stormtask_tasks_filter_reset'),
  );

  return $form;
}

function stormtask_tasks_filter_filter($form, &$form_state) {
  $_SESSION['stormtask_tasks_filter']['taskcategory'] = $form_state['values']['taskcategory'];
  $_SESSION['stormtask_tasks_filter']['taskstatus'] = $form_state['values']['taskstatus'];
  $_SESSION['stormtask_tasks_filter']['taskpriority'] = $form_state['values']['taskpriority'];
}

function stormtask_tasks_filter_reset($form, &$form_state) {
  unset($_SESSION['stormtask_tasks_filter']);
}

function _stormtask_project_tasks_js($project_nid) {
  $tree = _stormtask_get_tree($project_nid);
  $tasks = _stormtask_plain_tree($tree);
  print drupal_to_js($tasks);
  exit();
}

function stormtask_list() {
  $breadcrumb = array();
  $breadcrumb[] = l(t('Storm'), 'storm');
  drupal_set_breadcrumb($breadcrumb);

  if (array_key_exists('organization_nid', $_GET)) {
    if ($_SESSION['stormtask_list_filter']['organization_nid'] != $_GET['organization_nid']) {
      $_SESSION['stormtask_list_filter']['organization_nid'] = $_GET['organization_nid'];
    }
    unset($_SESSION['stormtask_list_filter']['project_nid']);
  }

  if (array_key_exists('project_nid', $_GET)) {
    if ($_SESSION['stormtask_list_filter']['project_nid'] != $_GET['project_nid']) {
      $_SESSION['stormtask_list_filter']['project_nid'] = $_GET['project_nid'];
    }
    $p = node_load($_GET['project_nid']);
    $_SESSION['stormtask_list_filter']['organization_nid'] = $p->organization_nid;

  }

  $o = drupal_get_form('stormtask_list_filter');

  $i = new stdClass();
  $i->type = 'stormtask';

  $header = array(
    array(
      'data' => t('Organization'),
      'field' => 'sta.organization_title',
    ),
    array(
      'data' => t('Project'),
      'field' => 'sta.project_title',
    ),
    array(
      'data' => t('Title'),
      'field' => 'n.title',
    ),
    array(
      'data' => t('Category'),
      'field' => 'sta.taskcategory',
    ),
    array(
      'data' => t('Status'),
      'field' => 'sta.taskstatus',
    ),
    array(
      'data' => t('Priority'),
      'field' => 'sta.taskpriority',
    ),
    array(
      'data' => storm_icon_add_node($i, $_GET),
      'class' => 'storm_list_operations',
    ),
  );

  $where = array();
  $args = array();

  $s  = "SELECT n.*, sta.* FROM {node} AS n INNER JOIN {stormtask} AS sta ON n.vid=sta.vid WHERE n.status=1 AND n.type='stormtask' ";
  if ($_SESSION['stormtask_list_filter']['organization_nid']) {
    $where[] = 'sta.organization_nid=%d';
    $args[] = $_SESSION['stormtask_list_filter']['organization_nid'];
  }
  if ($_SESSION['stormtask_list_filter']['project_nid']) {
    $where[] = 'sta.project_nid=%d';
    $args[] = $_SESSION['stormtask_list_filter']['project_nid'];
  }
  if ($_SESSION['stormtask_list_filter']['taskcategory'] && $_SESSION['stormtask_list_filter']['taskcategory'] != '-') {
    $category = split(',', $_SESSION['stormtask_list_filter']['taskcategory']);
    $v = array();
    foreach ($category as $item) $v[] = '%s';
    $where[] = "sta.taskcategory IN ('". implode("','",$v) ."')";
    foreach ($category as $key => $value) {
      $args[] = $value;
    }
  }
  if ($_SESSION['stormtask_list_filter']['taskstatus'] && $_SESSION['stormtask_list_filter']['taskstatus'] != '-') {
    $status = split(',', $_SESSION['stormtask_list_filter']['taskstatus']);
    $v = array();
    foreach ($status as $item) $v[] = '%s';
    $where[] = "sta.taskstatus IN ('". implode("','",$v) ."')";
    foreach ($status as $key => $value) {
      $args[] = $value;
    }
  }
  if ($_SESSION['stormtask_list_filter']['taskpriority'] && $_SESSION['stormtask_list_filter']['taskpriority'] != '-') {
    $priority = split(',', $_SESSION['stormtask_list_filter']['taskpriority']);
    $v = array();
    foreach ($priority as $item) $v[] = '%s';
    $where[] = "sta.taskpriority IN ('". implode("','",$v) ."')";
    foreach ($priority as $key => $value) {
      $args[] = $value;
    }
  }

  $datebeginfrom = $_SESSION['stormtask_list_filter']['datebeginfrom'];
  if ($datebeginfrom) {
    $datebeginfrom['hour'] = 0;
    $datebeginfrom['minute'] = 0;
    $t = _storm_datetime_to_gmtimestamp($datebeginfrom);
    if ($datebeginfrom['year']>0 && $t>=0) {
      $where[] = 'sta.datebegin>=%d';
      $args[] = $t;
    }
  }

  $datebeginto = $_SESSION['stormtask_list_filter']['datebeginto'];
  if ($datebeginto) {
    $datebeginto['hour'] = 23;
    $datebeginto['minute'] = 59;
    $t = _storm_datetime_to_gmtimestamp($datebeginto);
    if ($datebeginto['year']>0 && $t>=0) {
      $where[] = 'sta.datebegin<=%d';
      $args[] = $t;
    }
  }

  $dateendfrom = $_SESSION['stormtask_list_filter']['dateendfrom'];
  if ($dateendfrom) {
    $dateendfrom['hour'] = 0;
    $dateendfrom['minute'] = 0;
    $t = _storm_datetime_to_gmtimestamp($dateendfrom);
    if ($dateendfrom['year']>0 && $t>=0) {
      $where[] = 'sta.dateend>=%d';
      $args[] = $t;
    }
  }

  $dateendto = $_SESSION['stormtask_list_filter']['dateendto'];
  if ($dateendto) {
    $dateendto['hour'] = 23;
    $dateendto['minute'] = 59;
    $t = _storm_datetime_to_gmtimestamp($dateendto);
    if ($dateendto['year']>0 && $t>=0) {
      $where[] = 'sta.dateend<=%d';
      $args[] = $t;
    }
  }

  $itemsperpage = $_SESSION['stormtask_list_filter']['itemsperpage'];

  $s = stormtask_access_sql($s, $where);
  $s = db_rewrite_sql($s);

  $tablesort = tablesort_sql($header);
  $r = pager_query($s . $tablesort, $itemsperpage, 0, NULL, $args);

  $tasks = array();
  while ($item = db_fetch_object($r)) {
    $tasks[] = $item;
  }

  $o .= theme('stormtask_list', $header, $tasks);
  $o .= theme('pager', NULL, $itemperpage, 0);
  print theme('page', $o);
}

function stormtask_list_filter() {
  $category_list = stormattribute_attributes_bydomain('Task category search');
  $taskcategory = $_SESSION['stormtask_list_filter']['taskcategory'];
  if (!$taskcategory) {
    $taskcategory = $category_list['default'];
    $_SESSION['stormtask_list_filter']['taskcategory'] = $taskcategory;
  }

  $status_list = stormattribute_attributes_bydomain('Task status search');
  $taskstatus = $_SESSION['stormtask_list_filter']['taskstatus'];
  if (!$taskstatus) {
    $taskstatus = $status_list['default'];
    $_SESSION['stormtask_list_filter']['taskstatus'] = $taskstatus;
  }

  $priority_list = stormattribute_attributes_bydomain('Task priority search');
  $taskpriority = $_SESSION['stormtask_list_filter']['taskpriority'];
  if (!$taskpriority) {
    $taskpriority = $priority_list['default'];
    $_SESSION['stormtask_list_filter']['taskpriority'] = $taskpriority;
  }

  $organization_nid = $_SESSION['stormtask_list_filter']['organization_nid'];
  $project_nid = $_SESSION['stormtask_list_filter']['project_nid'];

  $datebeginfrom = $_SESSION['stormtask_list_filter']['datebeginfrom'];
  $datebeginto = $_SESSION['stormtask_list_filter']['datebeginto'];
  $dateendfrom = $_SESSION['stormtask_list_filter']['dateendfrom'];
  $dateendto = $_SESSION['stormtask_list_filter']['dateendto'];

  $itemsperpage = $_SESSION['stormtask_list_filter']['itemsperpage'];
  if (!$itemsperpage) {
    $itemsperpage = 10;
    $_SESSION['stormtask_list_filter']['itemsperpage'] = $itemsperpage;
  }

  $form = array();

  $form['filter'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filter'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['filter']['group1'] = array(
    '#type' => 'markup',
    '#theme' => 'storm_form_group',
    '#weight' => -20,
  );

  $s = "SELECT n.nid, n.title FROM {node} AS n INNER JOIN {stormorganization} AS sor ON sor.vid=n.vid WHERE n.status=1 AND n.type='stormorganization' ORDER BY n.title";
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
    '#attributes' => array('onchange' => "stormproject_organization_projects(this, 'edit-project-nid', true, 'All')"),
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
  );

  $form['filter']['group2'] = array(
    '#type' => 'markup',
    '#theme' => 'storm_form_group',
  );

  $form['filter']['group2']['taskcategory'] = array(
    '#type' => 'select',
    '#title' => t('Category'),
    '#default_value' => $taskcategory,
    '#options' => $category_list['values'],
  );

  $form['filter']['group2']['taskstatus'] = array(
    '#type' => 'select',
    '#title' => t('Status'),
    '#default_value' => $taskstatus,
    '#options' => $status_list['values'],
  );

  $form['filter']['group2']['taskpriority'] = array(
    '#type' => 'select',
    '#title' => t('Priority'),
    '#default_value' => $taskpriority,
    '#options' => $priority_list['values'],
  );

  $form['filter']['group3'] = array(
    '#type' => 'markup',
    '#theme' => 'storm_form_group',
  );

  $form['filter']['group3']['datebeginfrom'] = array(
    '#type' => 'dateext',
    '#withnull' => 'true',
    '#title' => t('Date begin from'),
    '#default_value' => $datebeginfrom,
  );

  $form['filter']['group3']['datebeginto'] = array(
    '#type' => 'dateext',
    '#withnull' => 'true',
    '#title' => t('Date begin to'),
    '#default_value' => $datebeginto,
  );

  $form['filter']['group4'] = array(
    '#type' => 'markup',
    '#theme' => 'storm_form_group',
  );

  $form['filter']['group4']['dateendfrom'] = array(
    '#type' => 'dateext',
    '#withnull' => 'true',
    '#title' => t('Date end from'),
    '#default_value' => $dateendfrom,
  );

  $form['filter']['group4']['dateendto'] = array(
    '#type' => 'dateext',
    '#withnull' => 'true',
    '#title' => t('Date end to'),
    '#default_value' => $dateendto,
  );

  $form['filter']['group5'] = array(
    '#type' => 'markup',
    '#theme' => 'storm_form_group',
  );

  $form['filter']['group5']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Filter'),
    '#submit' => array('stormtask_list_filter_filter'),
  );

  $form['filter']['group5']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset'),
    '#submit' => array('stormtask_list_filter_reset'),
  );

  $form['filter']['group5']['itemsperpage'] = array(
    '#type' => 'textfield',
    '#title' => t('Items'),
    '#size' => 10,
    '#default_value' => $itemsperpage,
    '#prefix' => '<div class="container-inline">',
    '#suffix' => '</div>',
  );

  return $form;
}

function stormtask_list_filter_filter($form, &$form_state) {
  $_SESSION['stormtask_list_filter']['organization_nid'] = $form_state['values']['organization_nid'];
  $_SESSION['stormtask_list_filter']['project_nid'] = $form_state['values']['project_nid'];
  $_SESSION['stormtask_list_filter']['taskcategory'] = $form_state['values']['taskcategory'];
  $_SESSION['stormtask_list_filter']['taskstatus'] = $form_state['values']['taskstatus'];
  $_SESSION['stormtask_list_filter']['taskpriority'] = $form_state['values']['taskpriority'];
  $_SESSION['stormtask_list_filter']['datebeginfrom'] = $form_state['values']['datebeginfrom'];
  $_SESSION['stormtask_list_filter']['datebeginto'] = $form_state['values']['datebeginto'];
  $_SESSION['stormtask_list_filter']['dateendfrom'] = $form_state['values']['dateendfrom'];
  $_SESSION['stormtask_list_filter']['dateendto'] = $form_state['values']['dateendto'];
  $_SESSION['stormtask_list_filter']['itemsperpage'] = $form_state['values']['itemsperpage'];
}

function stormtask_list_filter_reset($form, &$form_state) {
  unset($_SESSION['stormtask_list_filter']);
}

