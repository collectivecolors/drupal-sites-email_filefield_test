<?php
// $Id: stormproject.theme.inc,v 1.2.4.12 2009/07/24 21:58:17 magnity Exp $

/**
 * @file
 */

function theme_stormproject_list($header, $projects) {
  drupal_add_css(drupal_get_path('module', 'storm') .'/storm.css', 'module');

  $rows = array();
  foreach ($projects as $key => $project) {
    $n = new stdClass();
    $n->nid = $project->nid;
    $n->uid = $project->uid;
    $n->organization_nid = $project->organization_nid;
    $n->type = 'stormproject';

    $rows[] = array(
      storm_icon('projectcategory_'. $project->projectcategory, $project->projectcategory),
      l($project->organization_title, 'node/'. $project->organization_nid),
      l($project->title, 'node/'. $project->nid) . theme('mark', node_mark($project->nid, $project->changed)),
      storm_icon('status_'. $project->projectstatus, $project->projectstatus),
      storm_icon('priority_'. $project->projectpriority, $project->projectpriority),
      array(
        'data' => storm_icon_edit_node($n, $_GET) .'&nbsp;'. storm_icon_delete_node($n, $_GET),
        'class' => 'storm_list_operations',
      ),
    );
  }
  $o  = theme('table', $header, $rows);
  return $o;
}

function theme_stormproject_view($node, $teaser = FALSE, $page = FALSE) {
  $node = node_prepare($node, $teaser);

  $w = 0;
  $node->content['stormproject'] = array(
    '#prefix' => '<div id="stormproject" class="stormcomponent">',
    '#suffix' => '</div>',
    '#weight' => $w++,
  );

  $node->content['stormproject']['fields'] = array(
    '#prefix' => '<div id="fields">',
    '#suffix' => '</div>',
    '#weight' => $w++,
  );

  $node->content['stormproject']['fields']['organization'] = array(
    '#prefix' => '<div class="organization">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Organization'), l($node->organization_title, 'node/'. $node->organization_nid)),
    '#weight' => $w++,
  );
  $node->content['stormproject']['fields']['projectcategory'] = array(
    '#prefix' => '<div class="projectcategory">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Category'), stormattribute_value('Project category', $node->projectcategory)),
    '#weight' => $w++,
  );

  $node->content['stormproject']['fields']['projectstatus'] = array(
    '#prefix' => '<div class="projectstatus">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Status'), stormattribute_value('Project status', $node->projectstatus)),
    '#weight' => $w++,
  );

  $node->content['stormproject']['fields']['projectpriority'] = array(
    '#prefix' => '<div class="projectpriority">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Priority'), stormattribute_value('Project priority', $node->projectpriority)),
    '#weight' => $w++,
  );

  $node->content['stormproject']['fields']['body'] = array(
    '#prefix' => '<div class="body">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Description'), $node->content['body']['#value']),
    '#weight' => $w++,
  );
  unset($node->content['body']);

  $node->content['stormproject']['links'] = array(
    '#prefix' => '<div id="links">',
    '#suffix' => '</div>',
    '#weight' => $w++,
  );

  $w = 0;
  $i = new stdClass();
  
  $node->content['stormproject']['links']['expenses'] = theme_storm_link('stormproject', 'stormexpense', $node->nid, $w++);
  $node->content['stormproject']['links']['notes'] = theme_storm_link('stormproject', 'stormnote', $node->nid, $w++);
  $node->content['stormproject']['links']['tasks'] = theme_storm_link('stormproject', 'stormtask', $node->nid, $w++);
  $node->content['stormproject']['links']['tickets'] = theme_storm_link('stormproject', 'stormticket', $node->nid, $w++);  
  $node->content['stormproject']['links']['timetrackings'] = theme_storm_link('stormproject', 'stormtimetracking', $node->nid, $w++);
  
  return $node;
}