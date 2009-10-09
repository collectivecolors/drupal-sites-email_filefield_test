<?php
// $Id: stormattribute_handler_field_attributes_domain.inc,v 1.1.2.1 2009/08/12 17:34:51 magnity Exp $

/**
 * Show attribute values rather than keys in Storm Views fields.
 */

class stormattribute_handler_field_attributes_domain extends views_handler_field {

  function render($values) {
    $key = $values->{$this->field_alias};
    $value = stormattribute_value($this->definition['domain'], $key);
    return check_plain($value);
  }

}