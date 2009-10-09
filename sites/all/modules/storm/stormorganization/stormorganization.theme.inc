<?php
// $Id: stormorganization.theme.inc,v 1.2.4.15 2009/07/25 21:58:24 magnity Exp $

/**
 * @file
 */

function theme_stormorganization_list($header, $organizations) {
  drupal_add_css(drupal_get_path('module', 'storm') .'/storm.css', 'module');

  $rows = array();
  $countries = stormattribute_attributes_bydomain('Country');
  foreach ($organizations as $key => $organization) {
    $n = new stdClass();
    $n->nid = $organization->nid;
    $n->uid = $organization->uid;
    $n->type = 'stormorganization';

    $rows[] = array(
      l($organization->title, 'node/'. $organization->nid),
      $countries['values'][$organization->country],
      array(
        'data' => storm_icon_edit_node($n, $_GET) .'&nbsp;'. storm_icon_delete_node($n, $_GET),
        'class' => 'storm_list_operations',
      ),
    );
  }
  $o  = theme('table', $header, $rows);
  return $o;
}

function theme_stormorganization_view($node, $teaser = FALSE, $page = FALSE) {
  $node = node_prepare($node, $teaser);
  unset($node->content['body']);

  $w = 0;
  $node->content['stormorganization'] = array(
    '#prefix' => '<div id="stormorganization" class="stormcomponent">',
    '#suffix' => '</div>',
    '#weight' => $w++,
  );

  $node->content['stormorganization']['fields'] = array(
    '#prefix' => '<div id="fields">',
    '#suffix' => '</div>',
    '#weight' => $w++,
  );

  $w = 0;
  $node->content['stormorganization']['fields'] ['fullname'] = array(
    '#prefix' => '<div class="fullname">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Fullname'), $node->fullname),
    '#weight' => $w++,
  );

  $node->content['stormorganization']['fields'] ['country'] = array(
    '#prefix' => '<div class="country">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Country'), $node->country),
    '#weight' => $w++,
  );

  $node->content['stormorganization']['fields'] ['provstate'] = array(
    '#prefix' => '<div class="provstate">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Province / State'), $node->provstate),
    '#weight' => $w++,
  );

  $node->content['stormorganization']['fields'] ['city'] = array(
    '#prefix' => '<div class="city">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('City'), $node->city),
    '#weight' => $w++,
  );

  $node->content['stormorganization']['fields'] ['zip'] = array(
    '#prefix' => '<div class="zip">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Zip'), $node->zip),
    '#weight' => $w++,
  );

  $node->content['stormorganization']['fields'] ['address'] = array(
    '#prefix' => '<div class="address">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Address'), $node->address),
    '#weight' => $w++,
  );

  $node->content['stormorganization']['fields'] ['www'] = array(
    '#prefix' => '<div class="www">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('WWW'), l($node->www, 'http://'. $node->www, array('absolute' => TRUE))),
    '#weight' => $w++,
  );

  $node->content['stormorganization']['fields'] ['email'] = array(
    '#prefix' => '<div class="email">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Email'), l($node->email, 'mailto:'. $node->email, array('absolute' => TRUE))),
    '#weight' => $w++,
  );

  $node->content['stormorganization']['fields'] ['currency'] = array(
    '#prefix' => '<div class="currency">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Currency'), $node->currency),
    '#weight' => $w++,
  );

  $languages = language_list('language', TRUE);
  $languages_options = array();
  foreach ($languages as $language_code => $language) {
    $languages_options[$language_code] = $language->name;
  }

  $node->content['stormorganization']['fields'] ['language'] = array(
    '#prefix' => '<div class="language">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Language'), $languages_options[$node->orglanguage]),
    '#weight' => $w++,
  );

  $node->content['stormorganization']['fields'] ['taxid'] = array(
    '#prefix' => '<div class="taxid">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Tax ID'), $node->taxid),
    '#weight' => $w++,
  );

  $node->content['stormorganization']['fields'] ['note'] = array(
    '#prefix' => '<div class="note">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Note'), $node->body),
    '#weight' => $w++,
  );

  $node->content['stormorganization']['links'] = array(
    '#prefix' => '<div id="links">',
    '#suffix' => '</div>',
    '#weight' => $w++,
  );

  $w = 0;
  $i = new stdClass();
  
  $node->content['stormorganization']['links']['expenses'] = theme_storm_link('stormorganization', 'stormexpense', $node->nid, $w++);
  $node->content['stormorganization']['links']['invoices'] = theme_storm_link('stormorganization', 'storminvoice', $node->nid, $w++);
  $node->content['stormorganization']['links']['notes'] = theme_storm_link('stormorganization', 'stormnote', $node->nid, $w++);
  $node->content['stormorganization']['links']['people'] = theme_storm_link('stormorganization', 'stormperson', $node->nid, $w++);
  $node->content['stormorganization']['links']['projects'] = theme_storm_link('stormorganization', 'stormproject', $node->nid, $w++);
  $node->content['stormorganization']['links']['tasks'] = theme_storm_link('stormorganization', 'stormtask', $node->nid, $w++);
  $node->content['stormorganization']['links']['tickets'] = theme_storm_link('stormorganization', 'stormticket', $node->nid, $w++);
  $node->content['stormorganization']['links']['timetrackings'] = theme_storm_link('stormorganization', 'stormtimetracking', $node->nid, $w++);
  
  return $node;
}