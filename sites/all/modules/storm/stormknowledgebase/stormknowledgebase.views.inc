<?php
// $Id: stormknowledgebase.views.inc,v 1.1.2.4 2009/08/12 17:50:58 magnity Exp $

function stormknowledgebase_views_data() {
  $data['stormknowledgebase']['table']['group']  = 'Storm';
  $data['stormknowledgebase']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );
  
  $data['stormknowledgebase']['topic'] = array(
    'title' => t('Knowledgebase Topic'),
    'help' => 'Storm Knowledgebase Topic',
    'field' => array(
      'click sortable' => TRUE,
      'handler' => 'stormattribute_handler_field_attributes_domain',
      'domain' => 'Knowledge base topic',
    ),
    'filter' => array(
      'handler' => 'stormattribute_handler_filter_attributes_domain',
      'domain' => 'Knowledge base topic',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  return $data;
}

function stormknowledgebase_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'stormattribute'),
    ),
    'handlers' => array(
      'stormattribute_handler_field_attributes_domain' => array(
        'parent' => 'views_handler_field',
      ),
      'stormattribute_handler_filter_attributes_domain' => array(
        'parent' => 'views_handler_filter_in_operator',
      ),
    ),
  );
}
