<?php


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
