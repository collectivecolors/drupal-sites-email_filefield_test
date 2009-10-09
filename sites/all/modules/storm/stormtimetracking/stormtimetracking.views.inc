<?php
// $Id: stormtimetracking.views.inc,v 1.1.2.3 2009/07/25 00:42:13 magnity Exp $

function stormtimetracking_views_data() {
  $data['stormtimetracking']['table']['group']  = 'Storm';
  $data['stormtimetracking']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );
  
  $data['stormtimetracking']['organization_nid'] = array(
    'title' => t('Timetracking Organization Node ID'),
    'help' => 'Storm Timetracking Organization Node ID',
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
  
  $data['stormtimetracking']['organization_title'] = array(
    'title' => t('Timetracking Organization Title'),
    'help' => 'Storm Timetracking Organization Title',
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
  
  $data['stormtimetracking']['project_nid'] = array(
    'title' => t('Timetracking Project Node ID'),
    'help' => 'Storm Timetracking Project Node ID',
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
  
  $data['stormtimetracking']['project_title'] = array(
    'title' => t('Timetracking Project Title'),
    'help' => 'Storm Timetracking Project Title',
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
  
  $data['stormtimetracking']['task_nid'] = array(
    'title' => t('Timetracking Task Node ID'),
    'help' => 'Storm Timetracking Task Node ID',
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
  
  $data['stormtimetracking']['task_stepno'] = array(
    'title' => t('Timetracking Task Step Number'),
    'help' => 'Storm Timetracking Task Step Number',
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
  
  $data['stormtimetracking']['task_title'] = array(
    'title' => t('Timetracking Task Title'),
    'help' => 'Storm Timetracking Task Title',
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
  
  $data['stormtimetracking']['ticket_nid'] = array(
    'title' => t('Timetracking Ticket Node ID'),
    'help' => 'Storm Timetracking Ticket Node ID',
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
  
  $data['stormtimetracking']['ticket_title'] = array(
    'title' => t('Timetracking Ticket Title'),
    'help' => 'Storm Timetracking Ticket Title',
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
  
  $data['stormtimetracking']['trackingdate'] = array(
    'title' => t('Timetracking Tracking Date'),
    'help' => 'Storm Timetracking Tracking Date',
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
  
  $data['stormtimetracking']['timebegin'] = array(
    'title' => t('Timetracking Time Begin'),
    'help' => 'Storm Timetracking Time Begin',
    'field' => array(
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  
  $data['stormtimetracking']['timeend'] = array(
    'title' => t('Timetracking Time End'),
    'help' => 'Storm Timetracking Time End',
    'field' => array(
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  
  $data['stormtimetracking']['duration'] = array(
    'title' => t('Timetracking Duration'),
    'help' => 'Storm Timetracking Duration',
    'field' => array(
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  
  $data['stormtimetracking']['billable'] = array(
    'title' => t('Timetracking Billable'),
    'help' => 'Storm Timetracking Billable',
    'field' => array(
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  
  return $data;
}

function stormtimetracking_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'stormattribute'),
    ),
    'handlers' => array(
      'stormattribute_handler_filter_attributes_domain' => array(
        'parent' => 'views_handler_filter_in_operator',
    ),
    ),
  );
}
