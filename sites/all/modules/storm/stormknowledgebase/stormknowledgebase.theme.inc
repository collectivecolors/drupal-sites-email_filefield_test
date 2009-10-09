<?php
// $Id: stormknowledgebase.theme.inc,v 1.1.4.6 2009/07/05 16:41:45 magnity Exp $

/**
 * @file
 */

function theme_stormknowledgebase_list($header, $kbs) {
  $rows = array();
  $topics = stormattribute_attributes_bydomain('Knowledge base topic');

  foreach ($kbs as $kb) {
    $n = new stdClass();
    $n->nid = $kb->nid;
    $n->uid = $kb->uid;
    $n->type = 'stormknowledgebase';
    $rows[] = array(
      l($kb->title, 'node/'. $kb->nid),
      $topics[values][$kb->topic],
      array(
        'data' => storm_icon_edit_node($n, $_GET) .'&nbsp;'. storm_icon_delete_node($n, $_GET),
        'class' => 'storm_list_operations',
      ),
    );
  }
  $o = theme('table', $header, $rows);
  return $o;
}

function theme_stormknowledgebase_view($node, $teaser = FALSE, $page = FALSE) {
  $node = node_prepare($node, $teaser);

  $w = 0;
  $node->content['stormknowledgebase'] = array(
    '#prefix' => '<div id="stormknowledgebase" class="stormcomponent">',
    '#suffix' => '</div>',
    '#weight' => $w++,
  );

  $node->content['stormknowledgebase']['fields'] = array(
    '#prefix' => '<div id="fields">',
    '#suffix' => '</div>',
    '#weight' => $w++,
  );

  $node->content['stormknowledgebase']['fields']['topic'] = array(
    '#prefix' => '<div class="topic">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Topic'), stormattribute_value('Knowledge base topic', $node->topic)),
    '#weight' => $w++,
  );

  $node->content['stormknowledgebase']['fields']['body'] = array(
    '#prefix' => '<div class="body">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Description'), $node->content['body']['#value']),
    '#weight' => $w++,
  );
  unset($node->content['body']);

  $node->content['stormknowledgebase']['links'] = array(
    '#prefix' => '<div id="links">',
    '#suffix' => '</div>',
    '#value' => '&nbsp;',
    '#weight' => $w++,
  );

  return $node;
}

