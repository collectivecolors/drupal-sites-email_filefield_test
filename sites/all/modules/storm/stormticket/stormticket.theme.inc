<?php
// $Id: stormticket.theme.inc,v 1.5.4.10 2009/07/24 22:05:33 magnity Exp $

/**
 * @file
 */

function theme_stormticket_list($header, $tickets) {

  $rows = array();
  foreach ($tickets as $ticket) {
    $n = new stdClass();
    $n->nid = $ticket->nid;
    $n->uid = $ticket->uid;
    $n->organization_nid = $ticket->organization_nid;
    $n->type = 'stormticket';

    $rows[] = array(
      storm_icon('category_'. $ticket->ticketcategory, $ticket->ticketcategory),
      l($ticket->organization_title, 'node/'. $ticket->organization_nid),
      l($ticket->project_title, 'node/'. $ticket->project_nid),
      l($ticket->title, 'node/'. $ticket->nid) . theme('mark', node_mark($ticket->nid, $ticket->changed)),
      format_date($ticket->created, 'small'),
      storm_icon('status_'. $ticket->ticketstatus, $ticket->ticketstatus),
      storm_icon('priority_'. $ticket->ticketpriority, $ticket->ticketpriority),
      array(
        'data' => storm_icon_edit_node($n, $_GET) .'&nbsp;'. storm_icon_delete_node($n, $_GET),
        'class' => 'storm_list_operations',
      ),
    );
  }
  $o = theme('table', $header, $rows);
  return $o;
}

function theme_stormticket_view($node, $teaser = FALSE, $page = FALSE) {
  $node = node_prepare($node, $teaser);
  
  $w = 0;
  $node->content['stormticket'] = array(
    '#prefix' => '<div id="stormticket" class="stormcomponent">',
    '#suffix' => '</div>',
    '#weight' => $w++,
  );

  $node->content['stormticket']['fields'] = array(
    '#prefix' => '<div id="fields">',
    '#suffix' => '</div>',
    '#weight' => $w++,
  );

  $node->content['stormticket']['fields']['organization'] = array(
    '#prefix' => '<div class="organization">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Organization'), l($node->organization_title, 'node/'. $node->organization_nid)),
    '#weight' => $w++,
  );

  $node->content['stormticket']['fields']['project'] = array(
    '#prefix' => '<div class="project">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Project'), l($node->project_title, 'node/'. $node->project_nid)),
    '#weight' => $w++,
  );

  $node->content['stormticket']['fields']['task'] = array(
    '#prefix' => '<div class="task">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Task'), l($node->task_title, 'node/'. $node->task_nid)),
    '#weight' => $w++,
  );

  $node->content['stormticket']['fields']['category'] = array(
    '#prefix' => '<div class="category">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Category'), stormattribute_value('Ticket category', $node->ticketcategory)),
    '#weight' => $w++,
  );
  
  $node->content['stormticket']['fields']['status'] = array(
    '#prefix' => '<div class="storm_status">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Status'), stormattribute_value('Ticket status', $node->ticketstatus)),
    '#weight' => $w++,
  );

  $node->content['stormticket']['fields']['priority'] = array(
    '#prefix' => '<div class="priority">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Priority'), stormattribute_value('Ticket priority', $node->ticketpriority)),
    '#weight' => $w++,
  );
  
  $node->content['stormticket']['fields']['body'] = array(
    '#prefix' => '<div class="body">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Description'), $node->content['body']['#value']),
    '#weight' => $w++,
  );
  unset($node->content['body']);

  $node->content['stormticket']['links'] = array(
    '#prefix' => '<div id="links">',
    '#suffix' => '</div>',
    '#value' => '&nbsp;',
    '#weight' => $w++,
  );
  
  $w = 0;

  $i = new stdClass();
  
  $node->content['stormticket']['links']['expenses'] = theme_storm_link('stormticket', 'stormexpense', $node->nid, $w++);
  $node->content['stormticket']['links']['timetrackings'] = theme_storm_link('stormticket', 'stormtimetracking', $node->nid, $w++);
  
  return $node;
}