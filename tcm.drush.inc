<?php

/**
 * Clear tcm from the cache explicetely.
 */
function drush_tcm_post_cache_clear() {
  tcm_cache_clear();
  drush_log('Component cache was cleared', 'success');
}

