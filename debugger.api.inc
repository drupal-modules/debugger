<?php

/**
 * @file
 *   Include file for API functions
 *
 */

/**
 * Register new filepath into database
 */
function debugger_api_db_register_file($file) {
  static $fids = array();
  if ($file && !array_key_exists($file, $fids) && ($file_relative = debugger_api_get_relative_path($file))) {
    if (!($fids[$file] = db_select('debugger_files', 'f')->fields('f', array('fid'))->condition('file', $file_relative)->execute()->fetchField())) {
    // if (!($fids[$file] = db_query("SELECT fid FROM {debugger_files} WHERE filepath = ':file'", array(':file' => $file_relative))->execute()->fetchField())) {
      $fids[$file] = db_insert('debugger_files')->fields(array('filepath' =>  $file_relative, 'module' => debugger_api_module_via_file($file_relative)))->execute();
      // db_query("INSERT INTO {debugger_files} SET `filepath` = ':file', `module` = ':mod'", array(':file' => $file_relative, ':mod' => debugger_api_module_via_file($file_relative)));
      // $fids[$file] = db_last_insert_id('debugger_files', 'fid');
    }
  }
  return array_key_exists($file, $fids) ? $fids[$file] : FALSE;
}

/**
 * Get relative path of the filepath
 */
function debugger_api_get_relative_path($filepath) {
  return substr($filepath, strlen(getcwd())+1);
}

/**
 * Register new function into database.
 */
function debugger_api_db_register_function($name, $fid = 0, $line = 0, $args = '', $desc = '') {
  static $fncs = array();
  $s = ':'; // separator
  $key = $name . $s . $fid . $s . $line; // Generate the unique key.
  if (!array_key_exists($key, $fncs)) {
    try {
      $func = new ReflectionFunction($name);
      $line = $func->getStartLine();
      $fid = $fid ?: debugger_api_db_register_file($func->getFileName());
    } catch (ReflectionException $e) {
      // E.g. eval, include, require, include_once, require_once (https://bugs.php.net/bug.php?id=65875)
      // $e->getMessage()
    }
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
  return array_key_exists($key, $fncs) ? $fncs[$key] : FALSE;
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
        'query' => end(explode('?', $_SERVER["REQUEST_URI"])),
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
  $request_id = debugger_api_db_register_request();
  $menu_item = menu_get_item(); // If you see 'Fatal error: Call to undefined function node_load', please remove exit()/die() function from the code.
  $errors = debugger_api_drupal_error_handler();
  $traces = debugger_api_register_backtrace();
  $time = timer_stop('debugger');
  $page_args = count($menu_item['page_arguments']); // FIXME: convert into serialized string, i.e. $node->nid=123 as (node:123), etc.

  return db_update('debugger_requests')
    ->fields(array(
      'rpath' => $menu_item['path'],
      'fid' => (int)debugger_api_db_register_file($menu_item['include_file']),
      'fncid' => debugger_api_db_register_function($menu_item['page_callback']), // function id of the menu router callback
      'mem_fncid' => reset(current($traces['fncid_mem'])),
      'slow_fncid' => reset(current($traces['fncid_slow'])),
      'slow_qid' => $sqid ?: 0, // @todo: SQL query which was the slowest.
      'time' => $time['time'],
      'memory' => function_exists('memory_get_peak_usage') ? memory_get_peak_usage() : memory_get_usage(),
      'num_sql' => count($queries),
      'num_ticks' => reset(debugger_tick(TRUE)),
      'num_err' => count($errors['error']) + count($errors['parse error']),
      'num_warn' => count($errors['warning']) + count($errors['user warning']) + count($errors['strict warning']),
      'num_notices' => count($errors['notice']) + count($errors['user notice']),
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
  static $mods;
  if (isset($mods[$file])) { // if already saved...
    return $mods[$file]; // ...get from cache
  }
  $mods[$file] = '(unknown)';
  if (!strpos($file, '/') !== FALSE || strpos($file, 'includes/') === 0) {
    $mods[$file] = 'Drupal';
  } else if (($extension = end(explode('.', ($filename = basename($file))))) == 'module') { // check for .module extension and get the name
      $mods[$file] = substr($filename, 0, -1-strlen($extension));
  } else {
    $dirname = $file;
    do {
      if (($dirname = dirname($dirname)) && (strpos($dirname, '/') === FALSE)) {
        $mods[$file] = '(unknown)';
        break;
      }
    } while(!($mods[$file] = db_query("SELECT name FROM {system} WHERE filename LIKE ':dirname%%'", array(':dirname' => $dirname))->fetchField()));
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
    // $debugger_trace[$tick_counter . ':' . $time . ':' . $memory]  = $backtrace;
    if ($curr_thread = $backtrace[1]) {
      $file = array_key_exists('file', $curr_thread) ? $curr_thread['file'] : '(unknown)';
      $line = array_key_exists('line', $curr_thread) ? $curr_thread['line'] : 0;
      $args = isset($curr_thread['args']) ? count($curr_thread['args']) : ''; // FIXME: convert to some kind of string format
    }
    $function = $curr_thread['function'];
    $options = '';
    if (!($fid = debugger_api_db_register_file($file))) {
      // $fid = -debugger_api_db_register_file($backtrace[2]['file']); // if not found, use minus for parent
      // $line = $backtrace[2]['line']; // if not found, use minus for parent
    };
    $fncid = debugger_api_db_register_function($function, $fid, $line, count($args));
    $rid = debugger_api_db_register_request();
    $tid = debugger_api_db_register_trace($ptid, $fncid, $pfncid, $fid, $line, $rid, $time, $memory, $args, $options);
    // array_walk($backtrace, 'debugger_api_db_register_trace_callback');
    // $backtrace = '(' . implode("),\n(", array_map('implode', array_fill(0, count($backtrace), ','), $backtrace)) . ')';
    unset($backtrace[0], $backtrace[1]); // remove first two elements
    // foreach ($backtrace as $key => $tobj) { } // TODO: add option for looking deep into backtrace
    /* CHECK PERFORMANCE */
    $module = debugger_api_module_via_file(debugger_api_get_relative_path($file));
    $new_mem = current($fncid_mem);
    $new_time = current($fncid_slow);
    if ($memory > $new_mem[1]) { // check how much memory using this line
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

/* TODO: Do we need this function?
function _debugger_api_gen_values($values, $curr) {
  static $ptid = NULL;
  is_null($ptid) ? ($ptid = $values || $values = '') : 0;
  if ($values) {
    $values .= "'),\n('";
  }
  list($file, $line, $function, $args) = array(debugger_api_db_register_file($curr['file']), $curr['line'], debugger_api_db_register_function($curr['function']), count($curr['args']));
  $values .= "$ptid','" . implode("','", array($file, $function, $args));
  return $values;
}
 */

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

