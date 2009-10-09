<?php
// $Id: stormtask.theme.inc,v 1.3.4.15 2009/07/24 22:03:59 magnity Exp $

/**
 * @file
 */

function theme_stormtask_tasks($form) {
  if (count($form['tasks'])>0) {
    drupal_add_tabledrag('tasks', 'match', 'parent', 'task-parent-nid', 'task-parent-nid', 'task-nid', TRUE);
    drupal_add_tabledrag('tasks', 'order', 'sibling', 'task-weight'); 
  }

  $header = array();
  $row = array();

  $header = $form['header']['#value'];
  unset($form['header']);

  foreach (element_children($form['tasks']) as $key) {
    $form['tasks'][$key]['task_parent-nid_'. $key]['#attributes']['class'] = 'task-parent-nid';
    $form['tasks'][$key]['task_nid_'. $key]['#attributes']['class'] = 'task-nid';
    $form['tasks'][$key]['task_weight_'. $key]['#attributes']['class'] = 'task-weight';
    $durationunit = $form['tasks'][$key]['task_durationunit_'. $key]['#value'];

    $data = array(
      theme('indentation', $form['tasks'][$key]['task_depth_'. $key]['#value']) . drupal_render($form['tasks'][$key]['task_description_'. $key]),
      drupal_render($form['tasks'][$key]['task_category_'. $key]),
      drupal_render($form['tasks'][$key]['task_status_'. $key]),
      drupal_render($form['tasks'][$key]['task_priority_'. $key]),
      array(
        'data' => sprintf('%.2f', drupal_render($form['tasks'][$key]['task_duration_'. $key])) .' '. substr($durationunit, 0, 1), 
        'style' => 'text-align: right'),
      drupal_render($form['tasks'][$key]['task_parent-nid_'. $key]) . drupal_render($form['tasks'][$key]['task_nid_'. $key]),
      drupal_render($form['tasks'][$key]['task_weight_'. $key]),
      array(
        'data' => drupal_render($form['tasks'][$key]['task_operations_'. $key]),
        'class' => 'storm_list_operations',
      ),
    );
    $row['data'] = $data;
    $row['class'] = empty($row['class']) ? 'draggable' : $row['class'] .' draggable';
    $rows[] = $row;
  }
  $o = theme('table', $header, $rows, array('id' => 'tasks'));
  return $o;
}

function theme_stormtask_list($header, $tasks) {
  $rows = array();
  foreach ($tasks as $task) {
    $n = new stdClass();
    $n->nid = $task->nid;
    $n->uid = $task->uid;
    $n->organization_nid = $task->organization_nid;
    $n->type = 'stormtask';

    $rows[] = array(
      l($task->organization_title, 'node/'. $task->organization_nid),
      l($task->project_title, 'node/'. $task->project_nid),
      l($task->title, 'node/'. $task->nid) . theme('mark', node_mark($task->nid, $task->changed)),
      storm_icon('category_'. $task->taskcategory, $task->taskcategory),
      storm_icon('status_'. $task->taskstatus, $task->taskstatus),
      storm_icon('priority_'. $task->taskpriority, $task->taskpriority),
      array(
        'data' => storm_icon_edit_node($n, $_GET) .'&nbsp;'. storm_icon_delete_node($n, $_GET),
        'class' => 'storm_list_operations',
      ),
    );
  }
  $o = theme('table', $header, $rows);
  return $o;
}

function theme_stormtask_view($node, $teaser = FALSE, $page = FALSE) {
  $node = node_prepare($node, $teaser);

  $w = 0;
  $node->content['stormtask'] = array(
    '#prefix' => '<div id="stormtask" class="stormcomponent">',
    '#suffix' => '</div>',
    '#weight' => $w++,
  );

  $node->content['stormtask']['fields'] = array(
    '#prefix' => '<div id="fields">',
    '#suffix' => '</div>',
    '#weight' => $w++,
  );

  $node->content['stormtask']['fields']['organization'] = array(
    '#prefix' => '<div class="organization">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Organization'), l($node->organization_title, 'node/'. $node->organization_nid)),
    '#weight' => $w++,
  );

  $node->content['stormtask']['fields']['project'] = array(
    '#prefix' => '<div class="project">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Project'), l($node->project_title, 'node/'. $node->project_nid)),
    '#weight' => $w++,
  );

  $node->content['stormtask']['fields']['stepno'] = array(
    '#prefix' => '<div class="stepno">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Step no.'), $node->stepno),
    '#weight' => $w++,
  );

  $node->content['stormtask']['fields']['body'] = array(
    '#prefix' => '<div class="body">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Description'), $node->content['body']['#value']),
    '#weight' => $w++,
  );
  unset($node->content['body']);

  $node->content['stormtask']['links'] = array(
    '#prefix' => '<div id="links">',
    '#suffix' => '</div>',
    '#value' => '&nbsp;',
    '#weight' => $w++,
  );

  $w = 0;
  $i = new stdClass();

  $node->content['stormtask']['links']['expenses'] = theme_storm_link('stormtask', 'stormexpense', $node->nid, $w++);
  $node->content['stormtask']['links']['notes'] = theme_storm_link('stormtask', 'stormnote', $node->nid, $w++);
  $node->content['stormtask']['links']['tickets'] = theme_storm_link('stormtask', 'stormticket', $node->nid, $w++);
  $node->content['stormtask']['links']['timetrackings'] = theme_storm_link('stormtask', 'stormtimetracking', $node->nid, $w++);
  
  return $node;
}