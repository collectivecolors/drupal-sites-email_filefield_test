<?php
// $Id: storminvoice.auto_add.inc,v 1.1.2.3 2009/07/22 00:05:15 magnity Exp $

/**
 * @file
 * Contains functions relating to the Storm Invoice auto_add functionality
 * (creating invoices based on other Storm nodes)
 */
 
function storminvoice_auto_add($node, $invoice = NULL) {
  switch ($node->type) {
    case 'stormorganization':
      $invoice_nid = stormorganization_storminvoice_auto_add($node, $invoice);
      break;
    case 'stormproject':
      $invoice_nid = stormorganization_storminvoice_auto_add($node, $invoice);
      break;
    case 'stormtask':
      $invoice_nid = stormorganization_storminvoice_auto_add($node, $invoice);
      break;
    case 'stormticket':
      $invoice_nid = stormticket_storminvoice_auto_add($node, $invoice);
      break;
    case 'stormtimetracking':
      $invoice_nid = stormtimetracking_storminvoice_auto_add($node, $invoice);
      break;
    case 'stormexpense':
      $invoice_nid = stormexpense_storminvoice_auto_add($node, $invoice);
      break;
    default:
      drupal_set_message(t('This type of node cannot be automatically added to an invoice'), 'error');
      //watchdog - add link to record error in more detail?
      drupal_goto('node/'. $node->nid);
  }
  if($invoice) {
    drupal_set_message('The '. $node->type .' has been added to the selected invoice');
  }
  else {
    drupal_set_message('This invoice was created automatically from the selected '. $node->type .'.');
  }
  drupal_goto('node/'. $invoice_nid);
}

function storminvoice_auto_add_select() {
  $form['node'] = array(
    '#title' => t('Node'),
    '#type' => 'hidden',
    '#value' => arg(4),
  );
    
  $form['invoice'] = array(
    '#title' => t('Invoice'),
    '#type' => 'select',
    '#options' => array(),
    '#description' => t('Please choose the invoice that you would like to add to'),
  );
  
  // THIS CODE LOADS OPTIONS INTO THE INVOICE SELECTOR
  // Load the node object, but don't know how to handle it yet because it could be a node of several types.
  $node = node_load(arg(4));
  /* This function does not know the type of node that is being billed for. To avoid recording all relationships between the Storm nodes, 
    * we simply check for the existance of a parent node (perhaps project, task, ticket etc). Organization will always be set.
    * The invoices we show in the list are those that match these parents or where these attributes are not set.
    */
  
  if (($node->type == 'stormorganization') && !($node->organization_nid)) {
    $node->organization_nid = $node->nid;
  }
  else if (($node->type == 'stormproject') && !($node->project_nid)) {
    $node->project_nid = $node->nid;
  }
  
  $sql = "SELECT n.nid, n.title, sin.* FROM {node} AS n INNER JOIN {storminvoice} AS sin ON n.nid=sin.nid";
  // Ensure node is published, correct type. Always filter by Organization
  $sql .= " WHERE n.status=1 AND n.type='storminvoice' AND sin.organization_nid=". $node->organization_nid;
  
  if ($node->project_nid) {
    $sql .= " AND (sin.project_nid=". $node->project_nid ." OR sin.project_nid=0)";
  }
  
  $sql = storminvoice_access_sql($sql);
  $sql = db_rewrite_sql($sql);
  $r = db_query($sql);
  while ($r_invoice = db_fetch_object($r)) {
    $form['invoice']['#options'][$r_invoice->nid] = $r_invoice->number ." | ". $r_invoice->title;
  }
    
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Select'),
  );
  
  return $form;
}

function storminvoice_auto_add_select_submit($form_id, $form_state) {
  $node = node_load($form_state['values']['node']);
  $invoice = $form_state['values']['invoice'];
  storminvoice_auto_add($node, $invoice);
}