<?php
// $Id: storm.theme.inc,v 1.6.4.19 2009/07/30 18:12:47 magnity Exp $

/**
 * @file
 */

function theme_storm_form_group($form) {
  drupal_add_css(drupal_get_path('module', 'storm') .'/storm.css', 'module');

  $row = array();
  foreach (element_children($form) as $key) {
    array_push($row, drupal_render($form[$key]));
  }
  $rows[] = array('data' => $row, 'class' => 'formgroup');
  $output .= theme('table', array(), $rows, array('class' => 'formgroup'));
  return $output;
}

function theme_datetime($element) {
  return theme('form_element', $element, '<div class="container-inline">'. $element['#children'] .'</div>');
}

function theme_dateext($element) {
  return theme('form_element', $element, '<div class="container-inline">'. $element['#children'] .'</div>');
}

function theme_storm_list_report($header, $rows, $title, $footer) {
  $css_all_file = drupal_get_path('module', 'storm') .'/storm_list_report_all.css';
  $css_print_file = drupal_get_path('module', 'storm') .'/storm_list_report_print.css';
  $query_string = '?'. drupal_substr(variable_get('css_js_query_string', '0'), 0, 1);

  $o = "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n";
  $o .= '<html xmlns="http://www.w3.org/1999/xhtml">';
  $o .= '<head>';
  $o .= '<title>'. (drupal_get_title() ? strip_tags(drupal_get_title()) : variable_get('site_name', 'Drupal')) .'</title>';
  $o .= '<link type="text/css" rel="stylesheet" media="all" href="'. base_path() . $css_all_file . $query_string .'" />';
  $o .= '<link type="text/css" rel="stylesheet" media="print" href="'. base_path() . $css_print_file . $query_string .'" />';
  $o .= '</head>';
  $o .= '<body>';
  $o .= '<table class="storm_report_header"><tr>';
  $o .= '<td class="storm_report_myorganization">';
  $o .= '<div class="site_name">'. variable_get('site_name', '') .'</div>';
  $o .= '<div class="site_slogan">'. variable_get('site_slogan', '') .'</div>';
  $o .= '</td>';  $o .= '<td class="storm_report_header">'. variable_get('storm_report_header', '') .'</td>';
  $o .= '</tr></table>';
  $o .= '<div class="storm_list_report_title">'. $title .'</div>';
  $o .= '<div class="storm_list_report_data">';
  $o .= theme('table', $header, $rows);
  $o .= '</div>';
  $o .= '<div class="storm_list_report_footer">'. $footer .'</div>';
  $o .= '</body>';
  $o .= '</html>';

  return $o;
}

function theme_storm_report($header, $content, $title, $footer, $headtitle='') {
  $css_all_file = drupal_get_path('module', 'storm') .'/storm_report_all.css';
  $css_print_file = drupal_get_path('module', 'storm') .'/storm_report_print.css';
  $query_string = '?'. drupal_substr(variable_get('css_js_query_string', '0'), 0, 1);

  $o = "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n";
  $o .= '<html xmlns="http://www.w3.org/1999/xhtml">';
  $o .= '<head>';
  $o .= '<title>'. ($headtitle ? strip_tags($headtitle) : $title) .'</title>';
  $o .= '<link type="text/css" rel="stylesheet" media="all" href="'. base_path() . $css_all_file . $query_string .'" />';
  $o .= '<link type="text/css" rel="stylesheet" media="print" href="'. base_path() . $css_print_file . $query_string .'" />';
  $o .= '</head>';
  $o .= '<body>';
  $o .= '<table class="storm_report_header"><tr>';
  $myorg = node_load(variable_get('storm_organization_nid', 0));
  $o .= '<td class="storm_report_myorganization">';
  $o .= '<div class="site_name">'. variable_get('site_name', '') .'</div>';
  $o .= '<div class="site_slogan">'. variable_get('site_slogan', '') .'</div>';
  $o .= '</td>';
  $o .= '<td class="storm_report_header">'. variable_get('storm_report_header', '') .'</td>';
  $o .= '</tr></table>';
  $o .= '<div class="storm_report_title">'. $title .'</div>';
  $o .= '<div id="storm_report_content">';
  $o .= $content;
  $o .= '</div>';
  $o .= '<div class="storm_report_footer">'. $footer .'</div>';
  $o .= '</body>';
  $o .= '</html>';

  return $o;
}

function theme_storm_view_item($label, $value) {
  $o = '<div class="label"><span class="label">'. t($label) .' : </span></div><div class="value">'. $value .'</div>';
  return $o;
}

// See 498108: Proposed to refactor creation of Storm Dashboard
function theme_storm_dashboard() {
  $o = '<div id="stormdashboard">';
  $o .= '<dl class="stormdashboard">';
  
  $o .= '<div class="stormdashboard">';
  $o .= theme_storm_link('', 'stormorganization');
  $o .= theme_storm_link('', 'stormperson');
  $o .= theme_storm_link('', 'stormteammember');
  $o .= theme_storm_link('', 'stormproject');
  $o .= theme_storm_link('', 'stormtask');
  $o .= theme_storm_link('', 'stormticket');
  $o .= theme_storm_link('', 'stormtimetracking');
  $o .= '</div>';

  $o .= '<div class="stormdashboard">';
  $o .= theme_storm_link('', 'stormnote');
  $o .= theme_storm_link('', 'storminvoice');
  $o .= theme_storm_link('', 'stormexpense');
  $o .= theme_storm_link('', 'stormknowledgebase');
  $o .= theme_storm_link('', 'stormattribute');
  $o .= theme_storm_link('', 'stormconfiguration');
  
  $o .= '</div>';
  $o .= '</dl>';
  $o .= '</div>';
  return $o;
}

function theme_storm_link($source_module='', $destination_module='', $node_nid=0, $weight=0) {
  switch ($source_module) {
 
   case "stormorganization":
      $params_key = 'organization_nid';
      break;

    case "stormproject":
      $params_key = 'project_nid';
      break;

    case "stormtask":
      $params_key = 'task_nid';
      break;

    case "stormticket":
      $params_key = 'ticket_nid';
      break;
  }

  switch ($destination_module) {
    case "stormattribute":
      $user_access_check = 'Storm attribute: access';
      $list_text = 'Attributes';
      $list_path = 'storm/attributes/';
      $add_icon_type = 'stormattribute';
      $add_path = 'storm/attributes/add';
      $dt_id = 'stormattributes';
      break;

    case "stormconfiguration":
      $user_access_check = 'Storm: access administration pages';
      $list_text = 'Configuration';
      $list_path = 'admin/storm';
      $add_icon_type = '';
      $add_path = '';
      $dt_id = 'stormconfiguration';
      break;

    case "stormexpense":
      $user_access_check = 'Storm expense: access';
      $list_text = 'Expenses';
      $list_path = 'storm/expenses/';
      $add_icon_type = 'stormexpense';
      $add_path = 'node/add/'. $destination_module;
      $dt_id = 'stormexpenses';
      break;

    case "storminvoice":
      $user_access_check = 'Storm invoice: access';
      $list_text = 'Invoices';
      $list_path = 'storm/invoices/';
      $add_icon_type = 'storminvoice';
      $add_path = 'node/add/'. $destination_module;
      $dt_id = 'storminvoices';
      break;

    case "stormknowledgebase":
      $user_access_check = 'Storm knowledgebase: access';
      $list_text = 'Knowledge base';
      $list_path = 'storm/knowledgebase/';
      $add_icon_type = 'stormknowledgebase';
      $add_path = 'node/add/'. $destination_module;
      $dt_id = 'stormknowledgebase';
      break;

    case "stormnote":
      $user_access_check = 'Storm note: access';
      $list_text = 'Notes';
      $list_path = 'storm/notes/';
      $add_icon_type = 'stormnote';
      $add_path = 'node/add/'. $destination_module;
      $dt_id = 'stormnotes';
      break;

    case "stormorganization":
      $user_access_check = 'Storm organization: access';
      $list_text = 'Organizations';
      $list_path = 'storm/organizations/';
      $add_icon_type = 'stormorganization';
      $add_path = 'node/add/'. $destination_module;
      $dt_id = 'stormorganizations';
      break;

    case "stormperson":
      $user_access_check = 'Storm person: access';
      $list_text = 'People';
      $list_path = 'storm/people/';
      $add_icon_type = 'stormperson';
      $add_path = 'node/add/'. $destination_module;
      $dt_id = 'stormpeople';
      break;

    case "stormproject":
      $user_access_check = 'Storm project: access';
      $list_text = 'Projects';
      $list_path = 'storm/projects/';
      $add_icon_type = 'stormproject';
      $add_path = 'node/add/'. $destination_module;
      $dt_id = 'stormprojects';
      break;

    case "stormtask":
      $user_access_check = 'Storm task: access';
      $list_text = 'Tasks';
      $list_path = 'storm/tasks/';
      $add_icon_type = 'stormtask';
      $add_path = 'node/add/'. $destination_module;
      $dt_id = 'stormtasks';
      break;

    case "stormteammember":
      $user_access_check = 'Storm teammember: access';
      $list_text = 'Team members';
      $list_path = 'storm/teammembers/';
      $add_icon_type = 'stormteammember';
      $add_path = 'storm/teammembers/add';
      $dt_id = 'stormteammembers';
      break;

    case "stormticket":
      $user_access_check = 'Storm ticket: access';
      $list_text = 'Tickets';
      $list_path = 'storm/tickets/';
      $add_icon_type = 'stormticket';
      $add_path = 'node/add/'. $destination_module;
      $dt_id = 'stormtickets';
      break;

    case "stormtimetracking":
      $user_access_check = 'Storm timetracking: access';
      $list_text = 'Timetrackings';
      $list_path = 'storm/timetrackings/';
      $add_icon_type = 'stormtimetracking';
      $node_links_key = 'timetrackings';
      $add_path = 'node/add/'. $destination_module;
      $dt_id = 'stormtimetrackings';

      break;
  }

  if (($destination_module=='stormconfiguration' && user_access($user_access_check)) || (module_exists($destination_module) && user_access($user_access_check))) {
    if ($node_nid == 0) {
      $params = array();
    }
    else {
      $params = array('query' => array($params_key => $node_nid));
    }
    $v = l(t($list_text), $list_path, $params);
    
    if (!$add_icon_type=='') {
      $i->type = $add_icon_type;
      if ($node_nid == 0) {
        $params = $_GET;
      }
      else {
        $params = $_GET;
        $params[$params_key] = $node_nid;
      }
      $v .= storm_icon_add($add_path, $i, $params);
    }

    if ($node_nid == 0) {
      $r = '<dt id="'. $dt_id .'" class="stormcomponent">';
      $r .= $v;
      $r .= '</dt>';
    }
    else {
      $r = array(
        '#prefix' => '<dt id="'. $dt_id .'" class="stormcomponent">',
        '#suffix' => '</dt>',
        '#value' => $v,
        '#weight' => $weight,
      );
    }
    return $r;
  }
}