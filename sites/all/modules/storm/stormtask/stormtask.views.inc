<?php
// $Id: stormtask.views.inc,v 1.1.2.4 2009/08/12 17:58:31 magnity Exp $

function stormtask_views_data() {
  $data['stormtask']['table']['group']  = 'Storm';
  $data['stormtask']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );
  
  $data['stormtask']['stepno'] = array(
    'title' => t('Task Step Number'),
    'help' => 'Storm Task Step Number',
    'field' => array(
      'click sortable' => TRUE,
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
  
  $data['stormtask']['organization_nid'] = array(
    'title' => t('Task Organization Node ID'),
    'help' => 'Storm Task Organization Node ID',
    'field' => array(
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  
  $data['stormtask']['organization_title'] = array(
    'title' => t('Task Organization Title'),
    'help' => 'Storm Task Organization Title',
    'field' => array(
      'click sortable' => TRUE,
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
  
  $data['stormtask']['project_nid'] = array(
    'title' => t('Task Project Node ID'),
    'help' => 'Storm Task Project Node ID',
    'field' => array(
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['stormtask']['project_title'] = array(
    'title' => t('Task Project Title'),
    'help' => 'Storm Task Project Title',
    'field' => array(
      'click sortable' => TRUE,
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

  $data['stormtask']['parent_nid'] = array(
    'title' => t('Task Parent Task Node ID'),
    'help' => 'Storm Task Patent Task Node ID',
    'field' => array(
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['stormtask']['weight'] = array(
    'title' => t('Task Weight'),
    'help' => 'Storm Task Weight',
    'field' => array(
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['stormtask']['taskstatus'] = array(
    'title' => t('Task Status'),
    'help' => 'Storm Task Status',
    'field' => array(
      'click sortable' => TRUE,
      'handler' => 'stormattribute_handler_field_attributes_domain',
      'domain' => 'Task Status',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'stormattribute_handler_filter_attributes_domain',
      'domain' => 'Task Status',
    ),
  );

  $data['stormtask']['taskcategory'] = array(
    'title' => t('Task Category'),
    'help' => 'Storm Task Category',
    'field' => array(
      'click sortable' => TRUE,
      'handler' => 'stormattribute_handler_field_attributes_domain',
      'domain' => 'Task Category',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'stormattribute_handler_filter_attributes_domain',
      'domain' => 'Task Category',
    ),
  );

  $data['stormtask']['taskpriority'] = array(
    'title' => t('Task Priority'),
    'help' => 'Storm Task Priority',
    'field' => array(
      'click sortable' => TRUE,
      'handler' => 'stormattribute_handler_field_attributes_domain',
      'domain' => 'Task Priority',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'stormattribute_handler_filter_attributes_domain',
      'domain' => 'Task Priority',
    ),
  );

  $data['stormtask']['pricemode'] = array(
    'title' => t('Task Price Mode'),
    'help' => 'Storm Task Price Mode',
    'field' => array(
      'click sortable' => TRUE,
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

  $data['stormtask']['price'] = array(
    'title' => t('Task Price'),
    'help' => 'Storm Task Price',
    'field' => array(
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['stormtask']['currency'] = array(
    'title' => t('Task Currency'),
    'help' => 'Storm Task Currency',
    'field' => array(
      'click sortable' => TRUE,
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

  $data['stormtask']['datebegin'] = array(
    'title' => t('Task Date Begin'),
    'help' => 'Storm Task Date Begin',
    'field' => array(
      'click sortable' => TRUE,
      'handler' => 'views_handler_field_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['stormtask']['dateend'] = array(
    'title' => t('Task Date End'),
    'help' => 'Storm Task Date End',
    'field' => array(
      'click sortable' => TRUE,
      'handler' => 'views_handler_field_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['stormtask']['durationunit'] = array(
    'title' => t('Task Duration Unit'),
    'help' => 'Storm Task Duration Unit',
    'field' => array(
      'click sortable' => TRUE,
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

  $data['stormtask']['duration'] = array(
    'title' => t('Task Duration'),
    'help' => 'Storm Task Duration',
    'field' => array(
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  
  return $data;
}

function stormtask_views_handlers() {
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

/**
 * Implementation of hook_date_api_fields().
 * on behalf of core fields.
 * 
 * All modules that create custom fields that use the 
 * 'views_handler_field_date' handler can provide
 * additional information here about the type of
 * date they create so the date can be used by
 * the Date API views date argument and date filter.
 */
function stormtask_date_api_fields($field) {
  $values = array(
    'sql_type' => DATE_UNIX, 
    'tz_handling' => 'site',
    'timezone_field' => '', 
    'offset_field' => '', 
    'related_fields' => array(),
    'granularity' => array('year', 'month', 'day', 'hour', 'minute', 'second'),
  );

  switch ($field) {
    case 'stormtask.datebegin':
    case 'stormtask.dateend':
      return $values;
  }

}

/**
 * Implement hook_date_api_tables().
 */
function stormtask_date_api_tables() {
  return array('stormtask');
}