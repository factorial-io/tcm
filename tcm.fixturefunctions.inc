<?php


/**
 * Parse an argument for a fixture-function.
 */
function _tcm_parse_func_arg($func_arg, $options) {
  $func_arg = trim($func_arg);
  if ($func_arg == 'null') {
    return NULL;
  }
  if ($func_arg[0] == '@') {
    $func_arg = substr($func_arg, 1);
    if (isset($options[$func_arg])) {
      $func_arg = $options[$func_arg];
    }
  }
  return $func_arg;
}

/**
 * Parse all fixture functions and call them, if available.
 */
function _tcm_parse_fixture_function(&$elem, $fixture_functions, $options) {

  if (is_string($elem) && (strlen($elem) > 0) && ($elem[0] == '@')) {
    $pos_1 = strpos($elem, '(');
    $pos_2 = strpos($elem, ')');
    if (($pos_1 !== FALSE) && ($pos_2 !== FALSE)) {
      $func_name = substr($elem, 1, $pos_1 - 1);
      $params = substr($elem, $pos_1 + 1, $pos_2 - $pos_1 - 1);
      $func_args = array();
      if (!empty($params)) {
        $func_args = array_map(function($func_arg) use ($options) {
          return _tcm_parse_func_arg($func_arg, $options);
        }, explode(',', $params));
      }
      if (isset($fixture_functions[$func_name])) {
        $func_name = $fixture_functions[$func_name];
      }
      if (function_exists($func_name)) {
        $elem = call_user_func_array($func_name, $func_args);
      }
      else {
        drupal_set_message(t('Could not find fixture-function %function!', array(
          '%function' => $func_name,
        )), 'error');
      }
    }
  }
}

/**
 * Get lorem ipsum text as HTML.
 *
 * @param int $num_paragraphs
 *   num paragraphs to create
 * @param string $textLength
 *   length of the text (short|medium|long)
 * @param bool $decorate
 *   TRUE, if you want bold and italic text
 * @param bool $links
 *   TRUE, if you want to get links
 *
 * @return string
 *   created text
 */
function tcm_fixture_lorem_ipsum_html($num_paragraphs = 10, $text_length = 'medium', $decorate = FALSE, $links = FALSE) {

  $url = array('http://loripsum.net/api', $num_paragraphs, $text_length);
  if ($decorate) {
    $url[] = 'decorate';
  }
  if ($links) {
    $url[] = 'link';
  }

  $url = implode('/', $url);
  $cache_id = 'tcm_lorem_impsum:' . $url;
  if ($data = cache_get($cache_id)) {
    return $data->data;
  }

  $data = file_get_contents($url);

  cache_set($cache_id, $data);

  return $data;
}

/**
 * Create lorem ipsum text without any markup
 */
function tcm_fixture_lorem_ipsum($num_paragraphs = 10, $text_length = 'medium') {
  $html = tcm_fixture_lorem_ipsum_html($num_paragraphs, $text_length);
  return strip_tags($html);
}

/**
 * Fixture for an image
 */
function tcm_fixture_image($width = 400, $height = 300) {
  return "http://fillmurray.com/$width/$height";
}

function tcm_fixture_component($component_name, $data = NULL, $options= array()) {
  return component($component_name, $data, $options);
}
