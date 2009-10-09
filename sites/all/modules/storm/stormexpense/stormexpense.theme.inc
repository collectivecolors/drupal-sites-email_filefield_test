<?php
// $Id: stormexpense.theme.inc,v 1.1.4.12 2009/08/04 22:46:01 magnity Exp $

/**
 * @file
 */

function theme_stormexpense_list($header, $expenses, $totals) {
  $rows = array();
  foreach ($expenses as $expense) {
    $n = new stdClass();
    $n->nid = $expense->nid;
    $n->uid = $expense->uid;
    $n->organization_nid = $expense->organization_nid;
    $n->project_nid = $expense->project_nid;
    $n->task_nid = $expense->task_nid;
    $n->ticket_nid = $expense->ticket_nid;
    $n->type = 'stormexpense';
    $rows[] = array(
      l($expense->organization_title, 'node/'. $expense->organization_nid),
      l($expense->project_title, 'node/'. $expense->project_nid),
      l($expense->title, 'node/'. $expense->nid),
      format_date($expense->expensedate, 'custom', 'Y-m-d'),
      array('data' => sprintf('%.2f', $expense->total), 'align' => 'right'),
      array(
        'data' => storm_icon_edit_node($n, $_GET) .'&nbsp;'. storm_icon_delete_node($n, $_GET),
        'class' => 'storm_list_operations',
      ),
    );
  }
  $o = theme('table', $header, $rows);

  $header = array(
    array(
      'data' => t('Amount'),
      'style' => 'text-align: right;',
    ),
    array(
      'data' => variable_get('storm_tax1_name', 'VAT'),
      'style' => 'text-align: right;',
    ),
    array(
      'data' => variable_get('storm_tax2_name', 'Tax 2'),
      'style' => 'text-align: right;',
    ),
    array(
      'data' => t('Total'),
      'style' => 'text-align: right;',
    ),
  );

  $rows = array();
  $rows[] = array(
    array(
      'data' => sprintf('%.2f', $totals->t_amount),
      'style' => 'text-align: right;',
    ),
    array(
      'data' => sprintf('%.2f', $totals->t_tax1),
      'style' => 'text-align: right;',
    ),
    array(
      'data' => sprintf('%.2f', $totals->t_tax2),
      'style' => 'text-align: right;',
    ),
    array(
      'data' => sprintf('%.2f', $totals->t_total),
      'style' => 'text-align: right;',
    ),
  );

  $o .= theme('table', $header, $rows);

  return $o;
}

function theme_stormexpense_view($node, $teaser = FALSE, $page = FALSE) {
  $node = node_prepare($node, $teaser);

  $w = 0;
  $node->content['stormexpense'] = array(
    '#prefix' => '<div id="stormexpense" class="stormcomponent">',
    '#suffix' => '</div>',
    '#weight' => $w++,
  );

  $node->content['stormexpense']['fields'] = array(
    '#prefix' => '<div id="fields">',
    '#suffix' => '</div>',
    '#weight' => $w++,
  );

  $node->content['stormexpense']['fields']['organization'] = array(
    '#prefix' => '<div class="organization">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Organization'), l($node->organization_title, 'node/'. $node->organization_nid)),
    '#weight' => $w++,
  );

  $node->content['stormexpense']['fields']['project'] = array(
    '#prefix' => '<div class="project">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Project'), l($node->project_title, 'node/'. $node->project_nid)),
    '#weight' => $w++,
  );

  $node->content['stormexpense']['fields']['task'] = array(
    '#prefix' => '<div class="task">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Task'), l($node->task_title, 'node/'. $node->task_nid)),
    '#weight' => $w++,
  );

  $node->content['stormexpense']['fields']['ticket'] = array(
    '#prefix' => '<div class="ticket">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Ticket'), l($node->ticket_title, 'node/'. $node->ticket_nid)),
    '#weight' => $w++,
  );

  $node->content['stormexpense']['fields']['provider'] = array(
    '#prefix' => '<div class="provider">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Provider'), $node->provider_title),
    '#weight' => $w++,
  );

  $node->content['stormexpense']['fields']['expensedate'] = array(
    '#prefix' => '<div class="expensedate">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Date'), format_date($node->expensedate, 'custom', 'Y-m-d')),
    '#weight' => $w++,
  );

  $node->content['stormexpense']['fields']['amount'] = array(
    '#prefix' => '<div class="amount">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Amount'), sprintf('%.2f', $node->amount)),
    '#weight' => $w++,
  );

  if ($node->tax1) {
    $node->content['stormexpense']['fields']['tax1'] = array(
      '#prefix' => '<div class="tax">',
      '#suffix' => '</div>',
      '#value' => theme('storm_view_item', variable_get('storm_tax1_name', 'VAT'), sprintf('%.2f', $node->tax1)),
      '#weight' => $w++,
    );
  }

  if ($node->tax2) {
    $node->content['stormexpense']['fields']['tax2'] = array(
      '#prefix' => '<div class="tax">',
      '#suffix' => '</div>',
      '#value' => theme('storm_view_item', variable_get('storm_tax2_name', 'Tax 2'), sprintf('%.2f', $node->tax2)),
      '#weight' => $w++,
    );
  }
  
  if ($node->tax1 || $node->tax2) {
    $node->content['stormexpense']['fields']['total'] = array(
      '#prefix' => '<div class="total">',
      '#suffix' => '</div>',
      '#value' => theme('storm_view_item', t('Total'), sprintf('%.2f', $node->total)),
      '#weight' => $w++,
    );
  }

  $node->content['stormexpense']['fields']['body'] = array(
    '#prefix' => '<div class="body">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Description'), $node->content['body']['#value']),
    '#weight' => $w++,
  );
  unset($node->content['body']);

  $node->content['stormexpense']['links'] = array(
    '#prefix' => '<div id="links">',
    '#suffix' => '</div>',
    '#value' => '&nbsp;',
    '#weight' => $w++,
  );

  // Code to create invoice auto_add link
  if (module_exists('storminvoice') && user_access('Storm invoice: add')) {
    $v = '';
    $v .= '<strong>'. t('Invoice this item:') .'</strong>';
    $v .= '<ul>';
    $v .= '<li>'. l('Add to new invoice', 'storm/invoice/auto_add/new/'. $node->nid) .'</li>';
    $v .= '<li>'. l('Add to existing invoice', 'storm/invoice/auto_add/existing/'. $node->nid) .'</li>';
    $v .= '</ul>';
    
    $node->content['stormexpense']['links']['auto_invoice'] = array(
      '#prefix' => '<dt id="storminvoices" class="stormcomponent">',
      '#suffix' => '</dt>',
      '#value' => $v,
      '#weight' => $w++,
    );
  }
  
  return $node;
}

function theme_stormexpense_list_form_report_reports() {
  $reports = array(
      'std' => t('Standard'),
      'for_organization' => t('For an organization'),
      'for_organization_w_task' => t('For an org. with tasks'),
      'for_project' => t('For a project'),
  );

  return $reports;
}

function theme_stormexpense_list_report($report, $language, $expenses) {
  switch ($report) {
    case 'std':
      $header = array(
        t('Organization', array(), $language),
        t('Project', array(), $language),
        t('Title', array(), $language),
        t('Date', array(), $language),
        t('Total', array(), $language));
      $expenses_total = 0;
      foreach ($expenses as $expense) {
        $rows[] = array(
          $expense->organization_title,
          $expense->project_title,
          $expense->title,
          format_date($expense->expensedate, 'custom', 'Y-m-d'),
          array('data' => sprintf('%.2f', $expense->total), 'align' => 'right'),
        );
        $expenses_total += $expense->total;
      }
      $title  = '<h2>'. t('Expenses report', array(), $language) .'</h2><br />';
    break;
    case 'for_organization':
      $organization = node_load($_SESSION['stormexpense_list_filter']['organization_nid']);
      $header = array(
        t('Project', array(), $language),
        t('Title', array(), $language),
        t('Date', array(), $language),
        t('Total', array(), $language));
      $expenses_total = 0;
      foreach ($expenses as $expense) {
        $rows[] = array(
          $expense->project_title,
          $expense->title,
          format_date($expense->expensedate, 'custom', 'Y-m-d'),
          array('data' => sprintf('%.2f', $expense->total), 'align' => 'right'),
        );
        $expenses_total += $expense->total;
      }
      $title  = '<h2>'. t('Expenses report', array(), $language) .'</h2><br />';
      $title .= t('Organization : @organization', array('@organization' => $organization->fullname), $language) .'<br />';
    break;
    case 'for_organization_w_task':
      $organization = node_load($_SESSION['stormexpense_list_filter']['organization_nid']);
      $header = array(
        t('Project', 'expense', array(), $language),
        t('Task', 'expense', array(), $language),
        t('Title', 'expense', array(), $language),
        t('Date', 'expense', array(), $language),
        t('Total', 'expense', array(), $language));
      $total_duration = 0;
      foreach ($expenses as $expense) {
        $rows[] = array(
          $expense->project_title,
          $expense->task_title,
          $expense->title,
          format_date($expense->expensedate, 'custom', 'Y-m-d'),
          array('data' => sprintf('%.2f', $expense->total), 'align' => 'right'),
        );
        $expenses_total += $expense->total;
      }
      $title  = '<h2>'. t('Expenses report', array(), $language) .'</h2><br />';
      $title .= t('Organization : @organization', array('@organization' => $organization->fullname), $language) .'<br />';
    break;
    case 'for_project':
      $organization = node_load($_SESSION['stormexpense_list_filter']['organization_nid']);
      $project = node_load($_SESSION['stormexpense_list_filter']['project_nid']);

      $header = array(
        t('Task', 'expense', array(), $language),
        t('Title', 'expense', array(), $language),
        t('Date', 'expense', array(), $language),
        t('Total', 'expense', array(), $language));
      $total_duration = 0;
      foreach ($expenses as $expense) {
        $rows[] = array(
          $expense->task_title,
          $expense->title,
          format_date($expense->expensedate, 'custom', 'Y-m-d'),
          array('data' => sprintf('%.2f', $expense->total), 'align' => 'right'),
        );
        $expenses_total += $expense->total;
      }
      $title  = '<h2>'. t('Expenses report', array(), $language) .'</h2><br />';
      $title .= t('Organization : @organization', array('@organization' => $organization->fullname), $language) .'<br />';
      $title .= t('Project : @project', array('@project' => $project->title), $language) .'<br />';
    break;
  }
  $footer = '<h3>'. t('Expenses total : %expenses_total' , array('%expenses_total' => format_plural($expenses_total, '1', '@count', array(), $language)), $language) .'</h3>';
  return theme('storm_list_report', $header, $rows, $title, $footer);
}