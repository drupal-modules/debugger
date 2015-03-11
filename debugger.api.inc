<?php

/**
 * @file
 *   Include file for API functions
 *
 */

/**
 * Register new filepath into database
 */
function debugger_api_db_register_file($file = NULL) {
  static $fids = array();

  // Get data from cache or database if present.
  if (empty($fids)) {
    if ($cache = cache_get('debugger-files')) {
      $fids = $cache->data;
    } else {
      $res = db_select('debugger_files', 'f')->fields('f', array('fid', 'filepath'))->execute();
      while ($file = $res->fetchObject()) {
        $fids[$file->filepath] = $file->fid;
      }
    }
  }

  if (!$file) {
    return $fids; // Return all, if no arg.
  } else {
    $file = debugger_api_get_relative_path($file) ?: '(unknown)'; // Convert absolute path into relative.
    if (!array_key_exists($file, $fids)) {
      try {
        $fids[$file] = db_insert('debugger_files')->fields(array('filepath' => $file, 'module' => debugger_api_module_via_file($file)))->execute();
      } catch (PDOException $e) { // Integrity constraint violation (e.g. duplicate entry).
        cache_clear_all('debugger-files'); // Clearing cache, as probably it's out-of-date.
        return FALSE;
      }
    }
  }

  /*
  if ($file && !array_key_exists($file, $fids) && ($file_relative = debugger_api_get_relative_path($file))) {
    if (!($fids[$file] = db_select('debugger_files', 'f')->fields('f', array('fid'))->condition('file', $file_relative)->execute()->fetchField())) {
    // if (!($fids[$file] = db_query("SELECT fid FROM {debugger_files} WHERE filepath = ':file'", array(':file' => $file_relative))->execute()->fetchField())) {
      $fids[$file] = db_insert('debugger_files')->fields(array('filepath' =>  $file_relative, 'module' => debugger_api_module_via_file($file_relative)))->execute();
      // db_query("INSERT INTO {debugger_files} SET `filepath` = ':file', `module` = ':mod'", array(':file' => $file_relative, ':mod' => debugger_api_module_via_file($file_relative)));
      // $fids[$file] = db_last_insert_id('debugger_files', 'fid');
    }
  }
  */

  return array_key_exists($file, $fids) ? $fids[$file] : FALSE;
}

/**
 * Get relative path of the filepath
 */
function debugger_api_get_relative_path($filepath) {
  // @todo: Find a better way, when path is outside of webroot (http://stackoverflow.com/q/2637945/55075).
  return $filepath[0] == DIRECTORY_SEPARATOR ? str_replace(getcwd().DIRECTORY_SEPARATOR, '', $filepath) : $filepath;
}

/**
 * Register new function into database.
 */
function debugger_api_db_register_function($name = NULL) {
  static $fncs = array();

  // Get data from cache or database if present.
  if (empty($fncs)) {
    if ($cache = cache_get('debugger-functions')) {
      $fncs = $cache->data;
    } else {
      $res = db_select('debugger_functions', 'f')->fields('f', array('fncid', 'name'))->execute();
      while ($func = $res->fetchObject()) {
        $fncs[$func->name] = $func->fncid;
      }
    }
  }
  if (!$name) {
    return $fncs; // Return all, if no arg.
  } else if (!array_key_exists($name, $fncs)) {
    try {
      $func = new ReflectionFunction($name);
      if (!$func->isUserDefined()) {
        return FALSE; // Ignore all non-user defined functions (such as internal).
      }
      $name = $func->name;
      $line = $func->getStartLine();
      $args = $func->getNumberOfRequiredParameters();
      $doc = $func->getDocComment();
      $fid = debugger_api_db_register_file($func->getFileName());
    } catch (ReflectionException $e) {
      // E.g. eval, include, require, include_once, require_once (https://bugs.php.net/bug.php?id=65875)
      // $e->getMessage()
      return FALSE;
    }
    try {
      $fncs[$name] = db_insert('debugger_functions')
        ->fields(array(
          'name' => $name,
          'fid' => (int)$fid,
          'line' => $line,
          'args' => $args,
          'description' => $doc))
        ->execute();
    } catch (PDOException $e) { // Integrity constraint violation (e.g. duplicate entry).
      cache_clear_all('debugger-functions'); // Clearing cache, as probably it's out-of-date.
      return FALSE;
    }
  }

  /*
  $s = ':'; // separator
  $key = $name . $s . $fid . $s . $line; // Generate the unique key.
  if (!array_key_exists($key, $fncs)) {
    if (!($fncs[$key] = db_select('debugger_functions', 'f')
        ->fields('f', array('fncid'))
        ->condition('name', $name)
        ->condition('fid', $fid)
        ->execute()
        ->fetchField())) {
      $fncs[$key] = db_insert('debugger_functions')
        ->fields(array(
          'name' => $name,
          'fid' => (int)$fid,
          'line' => $line,
          'args' => $args,
          'description' => $desc))
        ->execute();
      // db_query("INSERT INTO {debugger_functions} SET `name` = '%s', `fid` = '%s', `line` = '%d', `args` = '%s', `description` = '%s'", $name, $fid, $line, $args, $desc);
      // $fncs[$key] = db_last_insert_id('debugger_functions', 'fncid');
    }
  }
  */

  return $name && array_key_exists($name, $fncs) ? $fncs[$name] : FALSE;
}

/**
 * Register new request into database.
 * 
 * Note: It should be executed before register_tick_function().
 */
function debugger_api_db_register_request() {
  global $user;
  static $rid = 0;
  // $query = // TODO: What here? All after '?'?

  debugger_api_db_register_file();     // Load files from cache.
  debugger_api_db_register_function(); // Load functions from cache.

  if (!$rid) {
    $rid = db_insert('debugger_requests')
      ->fields(array(
        'fncid' => 0,       // Placeholder.
        'fid' => 0,         // Placeholder.
        'mem_fncid' => 0,   // Placeholder.
        'slow_fncid' => 0,  // Placeholder.
        'slow_qid' => 0,    // Placeholder.
        'num_sql' => 0,     // Placeholder.
        'num_ticks' => 0,   // Placeholder.
        'num_err' => 0,     // Placeholder.
        'num_warn' => 0,    // Placeholder.
        'num_notices' => 0, // Placeholder.
        'path' => !empty($_GET['q']) ? $_GET['q'] : '/',
        'query' => @$_SERVER['QUERY_STRING'],
        'post' => serialize($_POST),
        'uid' => $user->uid,
        'timestamp' => time()
        ))
      ->execute();

    // $request_id = db_last_insert_id('debugger_requests', 'rid');
    timer_start('debugger');
  }
  return $rid; // Return request id.
}

/**
 * Update already registered request with new details
 */
function debugger_api_db_finish_request($options = array()) {
  global $user, $queries;
  if (!function_exists('menu_get_item')) {
    return; // In case Drupal wasn't properly bootstrapped, ignore finishing request.
  }
  $menu = menu_get_item(); // If you see 'Fatal error: Call to undefined function node_load', please remove exit()/die() function from the code.
  $request_id = debugger_api_db_register_request();
  $errors = debugger_api_drupal_error_handler();
  $traces = debugger_api_register_backtrace();
  $time = timer_stop('debugger');
  $page_args = count($menu['page_arguments']); // FIXME: convert into serialized string, i.e. $node->nid=123 as (node:123), etc.

  $fncid_mem = current($traces['fncid_mem']);
  $fncid_slow = current($traces['fncid_slow']);

  return db_update('debugger_requests')
    ->fields(array(
      'rpath' => $menu['path'],
      'fid' => (int)debugger_api_db_register_file($menu['include_file'] ?: '(unknown)'),
      'fncid' => (int)debugger_api_db_register_function($menu['page_callback'] ?: '(unknown)'), // function id of the menu router callback
      'mem_fncid' => (int)reset($fncid_mem),
      'slow_fncid' => (int)reset($fncid_slow),
      'slow_qid' => $sqid ?: 0, // @todo: SQL query which was the slowest.
      'time' => $time['time'],
      'memory' => function_exists('memory_get_peak_usage') ? memory_get_peak_usage() : memory_get_usage(),
      'num_sql' => count($queries),
      'num_ticks' => reset(debugger_tick(TRUE)),
      'num_err' => count(@$errors['error']) + count(@$errors['parse error']),
      'num_warn' => count(@$errors['warning']) + count(@$errors['user warning']) + count(@$errors['strict warning']),
      'num_notices' => count(@$errors['notice']) + count(@$errors['user notice']),
      'options' => serialize($options),
      ))
    ->condition('rid', $request_id)
    ->execute();
}

/**
 * Register new trace item
 */
function debugger_api_db_register_trace($ptid, $fncid, $pfncid, $fid, $line, $rid, $time_delta, $mem_delta, $args = '', $options = '') {
  static $traces = array();
  $s = ':'; // separator
  $key = $rid . $s . $fncid . $s . $pfncid . $s . $fid . $s . $line; // Generate a unique key.
  if (!array_key_exists($key, $traces)) {
    /*
    if (db_select('debugger_traces', 't')
        ->addExpression("CONCAT('fncid', '$s', 'pfncid', '$s', 'fid', '$s', 'line')", 'key')
        ->condition('name', $name)
        ->execute()
        ->fetchField()) {
      */
   if (!($traces[$key] = db_query("SELECT CONCAT('fncid', '$s', 'pfncid', '$s', 'fid', '$s', 'line') FROM {debugger_traces} WHERE fncid = ':fncid' AND pfncid = ':pfncid' AND fid = ':fid' AND line = ':line'", 
           array(':fncid' => $fncid, ':pfncid' => $pfncid, ':fid' => $fid, ':line' => $line))->fetchField())) {
      $traces[$key] = db_update('debugger_traces')
        ->fields(array(
          'ptid' => $ptid,
          'fncid' => $fncid,
          'pfncid' => $pfncid,
          'fid' => $fid,
          'line' => $line,
          'rid' => $rid,
          'time_delta' => $time_delta,
          'mem_delta' => $mem_delta,
          'args' => $args,
          'options' => $options,
          ))
        ->execute();
    } else {
      $traces[$key] = db_insert('debugger_traces')
        ->fields(array(
          'ptid' => $ptid,
          'fncid' => $fncid,
          'pfncid' => $pfncid,
          'fid' => $fid,
          'line' => $line,
          'rid' => $rid,
          'time_delta' => $time_delta,
          'mem_delta' => $mem_delta,
          'args' => $args,
          'options' => $options,
          ))
        ->execute();
    }
    // $traces[$key] = db_last_insert_id('debugger_traces', 'tid');
  }
  return array_key_exists($key, $traces) ? $traces[$key] : FALSE;
}

/**
 * Detect module name by file
 */
function debugger_api_module_via_file($file) {
  static $mods = array();
  $file = $file[0] == DIRECTORY_SEPARATOR ? debugger_api_get_relative_path($file) : $file;
  if (array_key_exists($file, $mods)) { // if already saved...
    return $mods[$file]; // ...get from cache
  }

  $mods[$file] = '(unknown)';
  if (strpos($file, 'includes/') === 0) {
    $mods[$file] = 'Drupal';
  } else if (stripos(strrev($file), 'eludom') === 0) { // Check for .module extension.
    $mods[$file] = basename($file, '.module'); // Get file name.
  } else {
    require_once 'includes/theme.inc';
    $list = module_list(FALSE, FALSE) + array_keys(list_themes()); // Get list of all module and theme names.
    $found = array_intersect(explode(DIRECTORY_SEPARATOR, $file), $list);
    $mods[$file] = current($found);
  } // end: else
  return $mods[$file];
}

/**
 * Register backtrace into db
 */
function debugger_api_register_backtrace($backtrace = NULL, $time = NULL, $memory = NULL, $tick_counter = NULL, $start = 2) {
  static $debugger_trace = array(), $ptid = 0, $pfncid = 0;
  static $fncid_slow = array(0 => 0), $fncid_mem = array(0 => 0);

  if (!is_null($backtrace)) {
    $thread = $backtrace[1];
    $function = $thread['function'];
    $line = @$curr_thread['line'] ?: 0;
    $args = @count($curr_thread['args']);

    $file = @$curr_thread['file'] ?: '(unknown)';
    $fid = debugger_api_db_register_file($file);
    $fncid = debugger_api_db_register_function($function);

    $rid = debugger_api_db_register_request();
    $tid = debugger_api_db_register_trace($ptid, $fncid, $pfncid, $fid, $line, $rid, $time, $memory, $args);

    /* CHECK PERFORMANCE */
    // $module = debugger_api_module_via_file($file);

    $new_mem = current($fncid_mem);
    $new_time = current($fncid_slow);
    if ($memory > $new_mem[1]) { // Check how much memory using this line.
      $fncid_mem = array($tid => array($fncid, $memory));
    }
    if ($time > $new_time[1]) {
      $fncid_slow = array($tid => array($fncid, $time));
    }

    /* SAVE PARENTS */
    $ptid = $tid;
    $pfncid = $fncid;
  } else {
    return
      array(
        'traces' => $debugger_trace,
        'fncid_slow' => $fncid_slow,
        'fncid_mem' => $fncid_mem,
      );
  }
}

/**
 * Log errors as defined by administrator.
 *
 * Error levels:
 * - 0 = Log errors to database.
 * - 1 = Log errors to database and to screen.
 */
function debugger_api_drupal_error_handler($errno = NULL, $message = NULL, $filename = NULL, $line = NULL, $context = NULL) {
  static $errors = array();
  if (error_reporting() == 0 || !isset($errno, $message, $filename, $line, $context)) {
    return $errors;
  }
  _drupal_error_handler($errno, $message, $filename, $line, $context); // Execute original callback.

  $types = array(1 => 'error', 2 => 'warning', 4 => 'parse error', 8 => 'notice', 16 => 'core error', 32 => 'core warning', 64 => 'compile error', 128 => 'compile warning', 256 => 'user error', 512 => 'user warning', 1024 => 'user notice', 2048 => 'strict warning', 4096 => 'recoverable fatal error', 8192 => 'deprecated', 16384 => 'user deprecated', 30719 => 'all errors and warning');
  $errors[$types[$errno]][] = array($message, $filename, $line); // Ignore $context because it'll use too much memory.
}

/**
 * Clear debugger related data from tables
 */
function debugger_api_clear_data() {
  db_truncate('debugger_traces')->execute();
  db_truncate('debugger_requests')->execute();
  db_truncate('debugger_functions')->execute();
  db_truncate('debugger_files')->execute();
  db_truncate('debugger_sql_queries')->execute();
}

