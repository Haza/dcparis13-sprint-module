<?php

/**
 * @file
 * Hooks provided by the Formatters module.
 */

/**
 * @addtogroup hooks
 * 
 */

/**
 * @todo Function description
 *
 * @return
 *   An array of formatters.
 */
function hook_formatters_component_info() {
  $components = array();

  return $components;
}

/**
 * @todo Function description
 *
 * @return
 *   An array of formatters.
 */
function hook_formatters_component_info_alter(&$components) {
  // @todo Fix this
  $components['my_simple_components']['settings']['length'] = 150;
}

/**
 * @} End of "addtogroup hooks".
 */
