<?php
// $Id: stormperson.theme.inc,v 1.3.4.4 2009/02/15 09:03:34 robertogerola Exp $

/**
 * @file
 */

function theme_stormperson_list($header, $people) {
  $rows = array();
  foreach ($people as $person) {
    $n = new stdClass();
    $n->nid = $person->nid;
    $n->uid = $person->uid;
    $n->organization_nid = $person->organization_nid;
    $n->type = 'stormperson';

    $rows[] = array(
      l($person->organization_title, 'node/'. $person->organization_nid),
      l($person->title, 'node/'. $person->nid) . theme('mark', node_mark($person->nid, $person->changed)),
      l($person->email, 'mailto:'. $person->email),
      array(
        'data' => storm_icon_edit_node($n, $_GET) .'&nbsp;'. storm_icon_delete_node($n, $_GET),
        'class' => 'storm_list_operations',
      ),
    );
  }
  $o = theme('table', $header, $rows);
  return $o;
}

function theme_stormperson_view($node, $teaser = FALSE, $page = FALSE) {
  $node = node_prepare($node, $teaser);
  unset($node->content['body']);

  $w = 0;
  $node->content['stormperson'] = array(
    '#prefix' => '<div id="stormperson" class="stormcomponent">',
    '#suffix' => '</div>',
    '#weight' => $w++,
  );

  $node->content['stormperson']['fields'] = array(
    '#prefix' => '<div id="fields">',
    '#suffix' => '</div>',
    '#weight' => $w++,
  );

  $node->content['stormperson']['fields']['organization'] = array(
    '#prefix' => '<div id="organization">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Organization'), l($node->organization_title, 'node/'. $node->organization_nid)),
    '#weight' => $w++,
  );

  $node->content['stormperson']['fields']['fullname'] = array(
    '#prefix' => '<div id="fullname">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Fullname'), $node->fullname),
    '#weight' => $w++,
  );

  $node->content['stormperson']['fields']['email'] = array(
    '#prefix' => '<div id="email">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Email'), l($node->email, 'mailto:'. $node->email, array('absolute' => TRUE))),
    '#weight' => $w++,
  );

  $node->content['stormperson']['fields']['www'] = array(
    '#prefix' => '<div id="www">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('WWW'), l($node->www, $node->www, array('absolute' => TRUE))),
    '#weight' => $w++,
  );

  $node->content['stormperson']['fields']['phone'] = array(
    '#prefix' => '<div id="phone">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Phone'), $node->phone),
    '#weight' => $w++,
  );

  $node->content['stormperson']['fields']['im'] = array(
    '#prefix' => '<div id="im">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('IM'), $node->im),
    '#weight' => $w++,
  );

  $node->content['stormperson']['links'] = array(
    '#prefix' => '<div id="links">',
    '#suffix' => '</div>',
    '#value' => '&nbsp;',
    '#weight' => $w++,
  );

  $w = 0;

  return $node;
}
