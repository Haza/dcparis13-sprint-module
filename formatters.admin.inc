<?php


/**
 * Menu callback; Listing of all current formatters.
 */
function formatters_admin_list() {
  $page = array();

  $styles = formatters_get_list();
  $page['formatters_admin_list'] = array(
    '#markup' => theme('formatters_admin_list', array('styles' => $styles)),
    '#attached' => array(
      'css' => array(drupal_get_path('module', 'formatters') . '/formatters.admin.css' => array()),
    ),
  );

  return $page;
}

/**
 * Form builder; Form for adding a new image style.
 *
 * @ingroup forms
 * @see image_style_add_form_submit()
 * @see image_style_name_validate()
 */
function formatters_add_form($form, &$form_state) {
  $form['name'] = array(
    '#type' => 'textfield',
    '#size' => '64',
    '#title' => t('Formatter name'),
    '#default_value' => '',
    '#description' => t('Use only lowercase alphanumeric characters, underscores (_), and hyphens (-).'),
    '#element_validate' => array('formatters_name_validate'),
    '#required' => TRUE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Create new formatter'),
  );

  return $form;
}

/**
 * Element validate function to ensure unique, URL safe style names.
 */
function formatters_name_validate($element, $form_state) {
  // Check for duplicates.
  $styles = formatters_get_list();
  if (isset($styles[$element['#value']]) && (!isset($form_state['image_style']['ffid']) || $styles[$element['#value']]['ffid'] != $form_state['image_style']['ffid'])) {
    form_set_error($element['#name'], t('The formatter name %name is already in use.', array('%name' => $element['#value'])));
  }

  // Check for illegal characters in image style names.
  if (preg_match('/[^0-9a-z_\-]/', $element['#value'])) {
    form_set_error($element['#name'], t('Please only use lowercase alphanumeric characters, underscores (_), and hyphens (-) for style names.'));
  }
}


/**
 * Returns HTML for the page containing the list of formatters
 *
 * @param $variables
 *   An associative array containing:
 *   - styles: An array of all the image styles returned by image_get_styles().
 *
 * @see image_get_styles()
 * @ingroup themeable
 */
function theme_formatters_admin_list($variables) {
  $styles = $variables['styles'];

  $header = array(t('Formatter name'), t('Settings'), array('data' => t('Operations'), 'colspan' => 3));
  $rows = array();
  foreach ($styles as $style) {
    $row = array();
    $row[] = l($style['name'], 'admin/config/formatters/edit/' . $style['name']);
    $link_attributes = array(
      'attributes' => array(
        'class' => array('image-style-link'),
      ),
    );
    /*if ($style['storage'] == IMAGE_STORAGE_NORMAL) {
      $row[] = t('Custom');
      $row[] = l(t('edit'), 'admin/config/media/image-styles/edit/' . $style['name'], $link_attributes);
      $row[] = l(t('delete'), 'admin/config/media/image-styles/delete/' . $style['name'], $link_attributes);
    }
    elseif ($style['storage'] == IMAGE_STORAGE_OVERRIDE) {
      $row[] = t('Overridden');
      $row[] = l(t('edit'), 'admin/config/media/image-styles/edit/' . $style['name'], $link_attributes);
      $row[] = l(t('revert'), 'admin/config/media/image-styles/revert/' . $style['name'], $link_attributes);
    }
    else {*/
      $row[] = t('Default');
      $row[] = l(t('edit'), 'admin/config/formatters/edit/' . $style['name'], $link_attributes);
      $row[] = '';
    /* } */
    $rows[] = $row;
  }

  if (empty($rows)) {
    $rows[] = array(array(
      'colspan' => 4,
      'data' => t('There are currently no styles. <a href="!url">Add a new one</a>.', array('!url' => url('admin/config/formatters/add'))),
    ));
  }

  return theme('table', array('header' => $header, 'rows' => $rows));

