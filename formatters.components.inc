<?php

/**
 * @file
 * Functions needed to execute image effects provided by Image module.
 */

/**
 * Implements hook_image_effect_info().
 */
function formatters_formatters_component_info() {
  $components = array(
    'trim' => array(
      'label' => t('Trim'),
      'help' => '',
      /*'effect callback' => 'image_resize_effect',
      'dimensions callback' => 'image_resize_dimensions',
      'form callback' => 'image_resize_form',
      'summary theme' => 'image_resize_summary',*/
    )
  );
  return $components;
}

