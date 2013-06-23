<?php


/**
 * Menu callback; Listing of all current formatters.
 */
function formatters_admin_list() {
  $page = array();

  $formatters = formatters_get_list();
  $page['formatters_admin_list'] = array(
    '#markup' => theme('formatters_admin_list', array('formatters' => $formatters)),
    '#attached' => array(
      'css' => array(drupal_get_path('module', 'formatters') . '/formatters.admin.css' => array()),
    ),
  );

  return $page;
}