<?php

/**
 * Clear tcm from the cache explicetely.
 */
function drush_tcm_post_cache_clear() {
  cache_clear_all('tcm:*', 'cache', TRUE);
}

