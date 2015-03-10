<?php
/**
 * @file
 * debugger.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function debugger_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'Debug Requests';
  $view->description = 'Debugger: Requests';
  $view->tag = 'debugger';
  $view->base_table = 'debugger_requests';
  $view->human_name = '';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options'] = '10, 20, 50, 100, 200, 500';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'rid' => 'rid',
    'path' => 'path',
    'rpath' => 'rpath',
    'name' => 'name',
    'query' => 'query',
    'name_1' => 'name_1',
    'name_2' => 'name_2',
    'slow_qid' => 'slow_qid',
    'uid' => 'uid',
    'time' => 'time',
    'memory' => 'memory',
    'num_sql' => 'num_sql',
    'num_ticks' => 'num_ticks',
    'num_err' => 'num_err',
    'num_warn' => 'num_warn',
    'num_notices' => 'num_notices',
    'timestamp' => 'timestamp',
  );
  $handler->display->display_options['style_options']['default'] = 'rid';
  $handler->display->display_options['style_options']['info'] = array(
    'rid' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'path' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'rpath' => array(
      'align' => '',
      'separator' => '',
    ),
    'name' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'query' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'name_1' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'name_2' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'slow_qid' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'uid' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'time' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'memory' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'num_sql' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'num_ticks' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'num_err' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'num_warn' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'num_notices' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'timestamp' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['order'] = 'desc';
  /* Relationship: Debugger: Requests: Function ID of the menu router callback */
  $handler->display->display_options['relationships']['fncid']['id'] = 'fncid';
  $handler->display->display_options['relationships']['fncid']['table'] = 'debugger_requests';
  $handler->display->display_options['relationships']['fncid']['field'] = 'fncid';
  $handler->display->display_options['relationships']['fncid']['label'] = 'Debugger: Function ID of menu callback';
  /* Relationship: Debugger: Requests: Function ID which used the most memory */
  $handler->display->display_options['relationships']['mem_fncid']['id'] = 'mem_fncid';
  $handler->display->display_options['relationships']['mem_fncid']['table'] = 'debugger_requests';
  $handler->display->display_options['relationships']['mem_fncid']['field'] = 'mem_fncid';
  /* Relationship: Debugger: Requests: Function ID which was the slowest */
  $handler->display->display_options['relationships']['slow_fncid']['id'] = 'slow_fncid';
  $handler->display->display_options['relationships']['slow_fncid']['table'] = 'debugger_requests';
  $handler->display->display_options['relationships']['slow_fncid']['field'] = 'slow_fncid';
  /* Field: Debugger: Requests: Request ID */
  $handler->display->display_options['fields']['rid']['id'] = 'rid';
  $handler->display->display_options['fields']['rid']['table'] = 'debugger_requests';
  $handler->display->display_options['fields']['rid']['field'] = 'rid';
  $handler->display->display_options['fields']['rid']['label'] = 'rid';
  /* Field: Debugger: Requests: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'debugger_requests';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['path']['alter']['path'] = 'admin/reports/debugger/path/[path]';
  $handler->display->display_options['fields']['path']['alter']['max_length'] = '15';
  $handler->display->display_options['fields']['path']['alter']['trim'] = TRUE;
  /* Field: Debugger: Requests: Router path */
  $handler->display->display_options['fields']['rpath']['id'] = 'rpath';
  $handler->display->display_options['fields']['rpath']['table'] = 'debugger_requests';
  $handler->display->display_options['fields']['rpath']['field'] = 'rpath';
  $handler->display->display_options['fields']['rpath']['alter']['max_length'] = '15';
  $handler->display->display_options['fields']['rpath']['alter']['trim'] = TRUE;
  /* Field: Debugger: Functions: Function name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'debugger_functions';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'fncid';
  $handler->display->display_options['fields']['name']['label'] = 'Function page callback';
  $handler->display->display_options['fields']['name']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['path'] = 'admin/reports/debugger/traces/function/[name]';
  $handler->display->display_options['fields']['name']['alter']['max_length'] = '20';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['name']['empty'] = '(non-existing)';
  $handler->display->display_options['fields']['name']['empty_zero'] = TRUE;
  /* Field: Debugger: Requests: Query path */
  $handler->display->display_options['fields']['query']['id'] = 'query';
  $handler->display->display_options['fields']['query']['table'] = 'debugger_requests';
  $handler->display->display_options['fields']['query']['field'] = 'query';
  $handler->display->display_options['fields']['query']['label'] = 'Query';
  $handler->display->display_options['fields']['query']['alter']['max_length'] = '15';
  $handler->display->display_options['fields']['query']['alter']['trim'] = TRUE;
  /* Field: Debugger: Functions: Function name */
  $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
  $handler->display->display_options['fields']['name_1']['table'] = 'debugger_functions';
  $handler->display->display_options['fields']['name_1']['field'] = 'name';
  $handler->display->display_options['fields']['name_1']['relationship'] = 'mem_fncid';
  $handler->display->display_options['fields']['name_1']['label'] = 'Function (the most memory)';
  $handler->display->display_options['fields']['name_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['name_1']['alter']['path'] = 'admin/reports/debugger/traces/function/[name_1]';
  $handler->display->display_options['fields']['name_1']['alter']['max_length'] = '20';
  $handler->display->display_options['fields']['name_1']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name_1']['alter']['trim'] = TRUE;
  /* Field: Debugger: Functions: Function name */
  $handler->display->display_options['fields']['name_2']['id'] = 'name_2';
  $handler->display->display_options['fields']['name_2']['table'] = 'debugger_functions';
  $handler->display->display_options['fields']['name_2']['field'] = 'name';
  $handler->display->display_options['fields']['name_2']['relationship'] = 'slow_fncid';
  $handler->display->display_options['fields']['name_2']['label'] = 'Function (the slowest)';
  $handler->display->display_options['fields']['name_2']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['name_2']['alter']['path'] = 'admin/reports/debugger/traces/function/[name_2]';
  $handler->display->display_options['fields']['name_2']['alter']['max_length'] = '20';
  $handler->display->display_options['fields']['name_2']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name_2']['alter']['trim'] = TRUE;
  /* Field: Debugger: Requests: Query ID which was the slowest */
  $handler->display->display_options['fields']['slow_qid']['id'] = 'slow_qid';
  $handler->display->display_options['fields']['slow_qid']['table'] = 'debugger_requests';
  $handler->display->display_options['fields']['slow_qid']['field'] = 'slow_qid';
  $handler->display->display_options['fields']['slow_qid']['label'] = 'Query ID (the slowest)';
  /* Field: Debugger: Requests: Total time */
  $handler->display->display_options['fields']['time']['id'] = 'time';
  $handler->display->display_options['fields']['time']['table'] = 'debugger_requests';
  $handler->display->display_options['fields']['time']['field'] = 'time';
  $handler->display->display_options['fields']['time']['label'] = 'Time';
  $handler->display->display_options['fields']['time']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['time']['precision'] = '0';
  $handler->display->display_options['fields']['time']['suffix'] = 'ms';
  /* Field: Debugger: Requests: Memory used */
  $handler->display->display_options['fields']['memory']['id'] = 'memory';
  $handler->display->display_options['fields']['memory']['table'] = 'debugger_requests';
  $handler->display->display_options['fields']['memory']['field'] = 'memory';
  $handler->display->display_options['fields']['memory']['suffix'] = 'b';
  /* Field: Debugger: Requests: Number of SQL queries */
  $handler->display->display_options['fields']['num_sql']['id'] = 'num_sql';
  $handler->display->display_options['fields']['num_sql']['table'] = 'debugger_requests';
  $handler->display->display_options['fields']['num_sql']['field'] = 'num_sql';
  $handler->display->display_options['fields']['num_sql']['label'] = 'SQL queries';
  /* Field: Debugger: Requests: Number of ticks */
  $handler->display->display_options['fields']['num_ticks']['id'] = 'num_ticks';
  $handler->display->display_options['fields']['num_ticks']['table'] = 'debugger_requests';
  $handler->display->display_options['fields']['num_ticks']['field'] = 'num_ticks';
  $handler->display->display_options['fields']['num_ticks']['label'] = 'Ticks';
  /* Field: Debugger: Requests: Number of error messages */
  $handler->display->display_options['fields']['num_err']['id'] = 'num_err';
  $handler->display->display_options['fields']['num_err']['table'] = 'debugger_requests';
  $handler->display->display_options['fields']['num_err']['field'] = 'num_err';
  $handler->display->display_options['fields']['num_err']['label'] = 'No of errors';
  /* Field: Debugger: Requests: Number of warning messages */
  $handler->display->display_options['fields']['num_warn']['id'] = 'num_warn';
  $handler->display->display_options['fields']['num_warn']['table'] = 'debugger_requests';
  $handler->display->display_options['fields']['num_warn']['field'] = 'num_warn';
  $handler->display->display_options['fields']['num_warn']['label'] = 'No of warnings';
  /* Field: Debugger: Requests: Number of notice messages */
  $handler->display->display_options['fields']['num_notices']['id'] = 'num_notices';
  $handler->display->display_options['fields']['num_notices']['table'] = 'debugger_requests';
  $handler->display->display_options['fields']['num_notices']['field'] = 'num_notices';
  $handler->display->display_options['fields']['num_notices']['label'] = 'No of notices';
  /* Field: Debugger: Requests: Timestamp */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'debugger_requests';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = 'Date';

  /* Display: Requests */
  $handler = $view->new_display('page', 'Requests', 'page_1');
  $handler->display->display_options['path'] = 'admin/reports/debugger/requests';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Requests';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Debugger Data';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $translatables['Requests'] = array(
    t('Defaults'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Debugger: Function ID of menu callback'),
    t('Debugger: Function ID which used the most memory'),
    t('Debugger: Function ID (the slowest)'),
    t('rid'),
    t('Path'),
    t('Router path'),
    t('Function page callback'),
    t('(non-existing)'),
    t('Query'),
    t('Function (the most memory)'),
    t('Function (the slowest)'),
    t('Query ID (the slowest)'),
    t('Time'),
    t('.'),
    t(','),
    t('ms'),
    t('Memory used'),
    t('b'),
    t('SQL queries'),
    t('Ticks'),
    t('No of errors'),
    t('No of warnings'),
    t('No of notices'),
    t('Date'),
    t('Requests'),
  );
  $export['Requests'] = $view;

  $view = new view();
  $view->name = 'Debug Files';
  $view->description = 'Debugger: Files';
  $view->tag = 'debugger';
  $view->base_table = 'debugger_files';
  $view->human_name = '';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options'] = '10, 20, 50, 100, 200, 500';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = 'module';
  $handler->display->display_options['style_options']['columns'] = array(
    'fid' => 'fid',
    'filepath' => 'filepath',
    'module' => 'module',
  );
  $handler->display->display_options['style_options']['default'] = 'fid';
  $handler->display->display_options['style_options']['info'] = array(
    'fid' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'filepath' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'module' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
  );
  /* Field: Debugger: Files: File ID */
  $handler->display->display_options['fields']['fid']['id'] = 'fid';
  $handler->display->display_options['fields']['fid']['table'] = 'debugger_files';
  $handler->display->display_options['fields']['fid']['field'] = 'fid';
  /* Field: Debugger: Files: File Path */
  $handler->display->display_options['fields']['filepath']['id'] = 'filepath';
  $handler->display->display_options['fields']['filepath']['table'] = 'debugger_files';
  $handler->display->display_options['fields']['filepath']['field'] = 'filepath';
  /* Field: Debugger: Files: Module */
  $handler->display->display_options['fields']['module']['id'] = 'module';
  $handler->display->display_options['fields']['module']['table'] = 'debugger_files';
  $handler->display->display_options['fields']['module']['field'] = 'module';
  $handler->display->display_options['fields']['module']['exclude'] = TRUE;

  /* Display: Debugger: Files */
  $handler = $view->new_display('page', 'Debugger: Files', 'page_1');
  $handler->display->display_options['path'] = 'admin/reports/debugger/files';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Files';
  $handler->display->display_options['menu']['weight'] = '0';
  $translatables['debugger_files'] = array(
    t('Defaults'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('File ID'),
    t('File Path'),
    t('Module'),
    t('Debugger: Files'),
  );
  $export['debugger_files'] = $view;

  $view = new view();
  $view->name = 'Debug Functions';
  $view->description = 'Debugger: Functions';
  $view->tag = 'debugger';
  $view->base_table = 'debugger_functions';
  $view->human_name = '';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = 'module';
  $handler->display->display_options['style_options']['columns'] = array(
    'fncid' => 'fncid',
    'name' => 'name',
    'description' => 'description',
    'filepath' => 'filepath',
    'line' => 'line',
    'module' => 'module',
  );
  $handler->display->display_options['style_options']['default'] = 'fncid';
  $handler->display->display_options['style_options']['info'] = array(
    'fncid' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'name' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'description' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'filepath' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'line' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'module' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = 'Function calls caught by debugger.';
  /* Relationship: Debugger: Functions: File ID */
  $handler->display->display_options['relationships']['fid']['id'] = 'fid';
  $handler->display->display_options['relationships']['fid']['table'] = 'debugger_functions';
  $handler->display->display_options['relationships']['fid']['field'] = 'fid';
  /* Field: Debugger: Functions: Function ID */
  $handler->display->display_options['fields']['fncid']['id'] = 'fncid';
  $handler->display->display_options['fields']['fncid']['table'] = 'debugger_functions';
  $handler->display->display_options['fields']['fncid']['field'] = 'fncid';
  /* Field: Debugger: Functions: Function name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'debugger_functions';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = 'Name';
  /* Field: Debugger: Functions: Description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'debugger_functions';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  /* Field: Debugger: Files: File Path */
  $handler->display->display_options['fields']['filepath']['id'] = 'filepath';
  $handler->display->display_options['fields']['filepath']['table'] = 'debugger_files';
  $handler->display->display_options['fields']['filepath']['field'] = 'filepath';
  $handler->display->display_options['fields']['filepath']['relationship'] = 'fid';
  /* Field: Debugger: Functions: Line */
  $handler->display->display_options['fields']['line']['id'] = 'line';
  $handler->display->display_options['fields']['line']['table'] = 'debugger_functions';
  $handler->display->display_options['fields']['line']['field'] = 'line';
  /* Field: Debugger: Files: Module */
  $handler->display->display_options['fields']['module']['id'] = 'module';
  $handler->display->display_options['fields']['module']['table'] = 'debugger_files';
  $handler->display->display_options['fields']['module']['field'] = 'module';
  $handler->display->display_options['fields']['module']['relationship'] = 'fid';
  $handler->display->display_options['fields']['module']['exclude'] = TRUE;

  /* Display: Functions */
  $handler = $view->new_display('page', 'Functions', 'page_1');
  $handler->display->display_options['path'] = 'admin/reports/debugger/functions';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Functions';
  $handler->display->display_options['menu']['weight'] = '0';
  $translatables['debugger_functions'] = array(
    t('Defaults'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Function calls caught by debugger.'),
    t('Debugger: File'),
    t('Function ID'),
    t('Name'),
    t('Description'),
    t('File Path'),
    t('Line'),
    t('Module'),
    t('Functions'),
  );
  $export['debugger_functions'] = $view;

  $view = new view();
  $view->name = 'Debug SQL Queries';
  $view->description = 'Debugger: SQL Queries';
  $view->tag = 'debugger';
  $view->base_table = 'debugger_sql_queries';
  $view->human_name = '';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'qid' => 'qid',
    'fncid' => 'fncid',
    'time' => 'time',
  );
  $handler->display->display_options['style_options']['default'] = 'qid';
  $handler->display->display_options['style_options']['info'] = array(
    'qid' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'fncid' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'time' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Empty data';
  $handler->display->display_options['empty']['area']['content'] = 'No data.';
  /* Field: Debugger: SQL Queries: Query ID */
  $handler->display->display_options['fields']['qid']['id'] = 'qid';
  $handler->display->display_options['fields']['qid']['table'] = 'debugger_sql_queries';
  $handler->display->display_options['fields']['qid']['field'] = 'qid';
  /* Field: Debugger: SQL Queries: Function ID */
  $handler->display->display_options['fields']['fncid']['id'] = 'fncid';
  $handler->display->display_options['fields']['fncid']['table'] = 'debugger_sql_queries';
  $handler->display->display_options['fields']['fncid']['field'] = 'fncid';
  /* Field: Debugger: SQL Queries: Execution time */
  $handler->display->display_options['fields']['time']['id'] = 'time';
  $handler->display->display_options['fields']['time']['table'] = 'debugger_sql_queries';
  $handler->display->display_options['fields']['time']['field'] = 'time';

  /* Display: Debugger: SQL Queries */
  $handler = $view->new_display('page', 'Debugger: SQL Queries', 'page_1');
  $handler->display->display_options['path'] = 'admin/reports/debugger/sql_queries';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'SQL';
  $handler->display->display_options['menu']['weight'] = '0';
  $translatables['debugger_sql_queries'] = array(
    t('Defaults'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Empty data'),
    t('No data.'),
    t('Query ID'),
    t('Function ID'),
    t('Execution time'),
    t('.'),
    t(','),
    t('Debugger: SQL Queries'),
  );
  $export['debugger_sql_queries'] = $view;

  $view = new view();
  $view->name = 'debugger_traces';
  $view->description = 'Debugger: Traces';
  $view->tag = 'debugger';
  $view->base_table = 'debugger_traces';
  $view->human_name = '';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options'] = '10, 20, 50, 100, 200, 500';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = 'name_2';
  $handler->display->display_options['style_options']['columns'] = array(
    'tid' => 'tid',
    'ptid' => 'ptid',
    'name_1' => 'name_1',
    'name' => 'name',
    'pfncid' => 'pfncid',
    'fid' => 'fid',
    'filepath' => 'filepath',
    'line' => 'line',
    'rid' => 'rid',
    'time_delta' => 'time_delta',
    'mem_delta' => 'mem_delta',
    'name_2' => 'name_2',
  );
  $handler->display->display_options['style_options']['default'] = 'time_delta';
  $handler->display->display_options['style_options']['info'] = array(
    'tid' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'ptid' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'name_1' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'name' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'pfncid' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'fid' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'filepath' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'line' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'rid' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'time_delta' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'mem_delta' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'name_2' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['order'] = 'desc';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Empty data';
  $handler->display->display_options['empty']['area']['content'] = 'No traces found.';
  /* Relationship: Debugger: Traces: Request ID */
  $handler->display->display_options['relationships']['rid']['id'] = 'rid';
  $handler->display->display_options['relationships']['rid']['table'] = 'debugger_traces';
  $handler->display->display_options['relationships']['rid']['field'] = 'rid';
  $handler->display->display_options['relationships']['rid']['label'] = 'Debugger: Request';
  /* Relationship: Debugger: Traces: File ID */
  $handler->display->display_options['relationships']['fid']['id'] = 'fid';
  $handler->display->display_options['relationships']['fid']['table'] = 'debugger_traces';
  $handler->display->display_options['relationships']['fid']['field'] = 'fid';
  /* Relationship: Debugger: Traces: Function ID */
  $handler->display->display_options['relationships']['fncid']['id'] = 'fncid';
  $handler->display->display_options['relationships']['fncid']['table'] = 'debugger_traces';
  $handler->display->display_options['relationships']['fncid']['field'] = 'fncid';
  /* Relationship: Debugger: Traces: Function ID of parent */
  $handler->display->display_options['relationships']['pfncid']['id'] = 'pfncid';
  $handler->display->display_options['relationships']['pfncid']['table'] = 'debugger_traces';
  $handler->display->display_options['relationships']['pfncid']['field'] = 'pfncid';
  /* Relationship: Debugger: Requests: Function ID of the menu router callback */
  $handler->display->display_options['relationships']['fncid_1']['id'] = 'fncid_1';
  $handler->display->display_options['relationships']['fncid_1']['table'] = 'debugger_requests';
  $handler->display->display_options['relationships']['fncid_1']['field'] = 'fncid';
  $handler->display->display_options['relationships']['fncid_1']['relationship'] = 'rid';
  $handler->display->display_options['relationships']['fncid_1']['label'] = 'Debugger: Function of menu callback';
  /* Field: Debugger: Traces: Trace ID */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'debugger_traces';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  /* Field: Debugger: Traces: Trace ID of parent */
  $handler->display->display_options['fields']['ptid']['id'] = 'ptid';
  $handler->display->display_options['fields']['ptid']['table'] = 'debugger_traces';
  $handler->display->display_options['fields']['ptid']['field'] = 'ptid';
  /* Field: Debugger: Traces: Request ID */
  $handler->display->display_options['fields']['rid_1']['id'] = 'rid_1';
  $handler->display->display_options['fields']['rid_1']['table'] = 'debugger_traces';
  $handler->display->display_options['fields']['rid_1']['field'] = 'rid';
  $handler->display->display_options['fields']['rid_1']['label'] = 'rid';
  /* Field: Debugger: Requests: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'debugger_requests';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['relationship'] = 'rid';
  $handler->display->display_options['fields']['path']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['path']['alter']['path'] = '[path]';
  $handler->display->display_options['fields']['path']['empty'] = '(front)';
  /* Field: Debugger: Functions: Function name */
  $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
  $handler->display->display_options['fields']['name_1']['table'] = 'debugger_functions';
  $handler->display->display_options['fields']['name_1']['field'] = 'name';
  $handler->display->display_options['fields']['name_1']['relationship'] = 'fncid';
  $handler->display->display_options['fields']['name_1']['label'] = 'Function';
  /* Field: Debugger: Functions: Function name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'debugger_functions';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'pfncid';
  $handler->display->display_options['fields']['name']['label'] = 'Function parent';
  /* Field: Debugger: Files: Module */
  $handler->display->display_options['fields']['module']['id'] = 'module';
  $handler->display->display_options['fields']['module']['table'] = 'debugger_files';
  $handler->display->display_options['fields']['module']['field'] = 'module';
  $handler->display->display_options['fields']['module']['relationship'] = 'fid';
  /* Field: Debugger: Traces: Function ID */
  $handler->display->display_options['fields']['fncid']['id'] = 'fncid';
  $handler->display->display_options['fields']['fncid']['table'] = 'debugger_traces';
  $handler->display->display_options['fields']['fncid']['field'] = 'fncid';
  /* Field: Debugger: Traces: Function ID of parent */
  $handler->display->display_options['fields']['pfncid']['id'] = 'pfncid';
  $handler->display->display_options['fields']['pfncid']['table'] = 'debugger_traces';
  $handler->display->display_options['fields']['pfncid']['field'] = 'pfncid';
  /* Field: Debugger: Traces: File ID */
  $handler->display->display_options['fields']['fid']['id'] = 'fid';
  $handler->display->display_options['fields']['fid']['table'] = 'debugger_traces';
  $handler->display->display_options['fields']['fid']['field'] = 'fid';
  $handler->display->display_options['fields']['fid']['empty_zero'] = TRUE;
  /* Field: Debugger: Files: File Path */
  $handler->display->display_options['fields']['filepath']['id'] = 'filepath';
  $handler->display->display_options['fields']['filepath']['table'] = 'debugger_files';
  $handler->display->display_options['fields']['filepath']['field'] = 'filepath';
  $handler->display->display_options['fields']['filepath']['relationship'] = 'fid';
  /* Field: Debugger: Traces: Line */
  $handler->display->display_options['fields']['line']['id'] = 'line';
  $handler->display->display_options['fields']['line']['table'] = 'debugger_traces';
  $handler->display->display_options['fields']['line']['field'] = 'line';
  /* Field: Debugger: Traces: Request ID */
  $handler->display->display_options['fields']['rid']['id'] = 'rid';
  $handler->display->display_options['fields']['rid']['table'] = 'debugger_traces';
  $handler->display->display_options['fields']['rid']['field'] = 'rid';
  $handler->display->display_options['fields']['rid']['empty_zero'] = TRUE;
  /* Field: Debugger: Traces: Time Delta */
  $handler->display->display_options['fields']['time_delta']['id'] = 'time_delta';
  $handler->display->display_options['fields']['time_delta']['table'] = 'debugger_traces';
  $handler->display->display_options['fields']['time_delta']['field'] = 'time_delta';
  $handler->display->display_options['fields']['time_delta']['label'] = 'Time Delta (ms)';
  $handler->display->display_options['fields']['time_delta']['separator'] = ' ,';
  /* Field: Debugger: Traces: Memory delta */
  $handler->display->display_options['fields']['mem_delta']['id'] = 'mem_delta';
  $handler->display->display_options['fields']['mem_delta']['table'] = 'debugger_traces';
  $handler->display->display_options['fields']['mem_delta']['field'] = 'mem_delta';
  /* Field: Debugger: Functions: Function name */
  $handler->display->display_options['fields']['name_2']['id'] = 'name_2';
  $handler->display->display_options['fields']['name_2']['table'] = 'debugger_functions';
  $handler->display->display_options['fields']['name_2']['field'] = 'name';
  $handler->display->display_options['fields']['name_2']['relationship'] = 'fncid_1';
  $handler->display->display_options['fields']['name_2']['label'] = 'Menu callback function';
  $handler->display->display_options['fields']['name_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name_2']['empty'] = '(unknown)';
  /* Sort criterion: Debugger: Traces: Time Delta */
  $handler->display->display_options['sorts']['time_delta']['id'] = 'time_delta';
  $handler->display->display_options['sorts']['time_delta']['table'] = 'debugger_traces';
  $handler->display->display_options['sorts']['time_delta']['field'] = 'time_delta';
  /* Filter criterion: Debugger: Files: Module */
  $handler->display->display_options['filters']['module']['id'] = 'module';
  $handler->display->display_options['filters']['module']['table'] = 'debugger_files';
  $handler->display->display_options['filters']['module']['field'] = 'module';
  $handler->display->display_options['filters']['module']['relationship'] = 'fid';
  $handler->display->display_options['filters']['module']['operator'] = 'not in';
  $handler->display->display_options['filters']['module']['exposed'] = TRUE;
  $handler->display->display_options['filters']['module']['expose']['operator_id'] = 'module_op';
  $handler->display->display_options['filters']['module']['expose']['label'] = 'Module';
  $handler->display->display_options['filters']['module']['expose']['use_operator'] = TRUE;
  $handler->display->display_options['filters']['module']['expose']['operator'] = 'module_op';
  $handler->display->display_options['filters']['module']['expose']['identifier'] = 'module';
  /* Filter criterion: Debugger: Requests: Router path */
  $handler->display->display_options['filters']['rpath']['id'] = 'rpath';
  $handler->display->display_options['filters']['rpath']['table'] = 'debugger_requests';
  $handler->display->display_options['filters']['rpath']['field'] = 'rpath';
  $handler->display->display_options['filters']['rpath']['relationship'] = 'rid';
  $handler->display->display_options['filters']['rpath']['exposed'] = TRUE;
  $handler->display->display_options['filters']['rpath']['expose']['operator_id'] = 'rpath_op';
  $handler->display->display_options['filters']['rpath']['expose']['label'] = 'Router path';
  $handler->display->display_options['filters']['rpath']['expose']['use_operator'] = TRUE;
  $handler->display->display_options['filters']['rpath']['expose']['operator'] = 'rpath_op';
  $handler->display->display_options['filters']['rpath']['expose']['identifier'] = 'rpath';
  /* Filter criterion: Debugger: Traces: Time Delta */
  $handler->display->display_options['filters']['time_delta']['id'] = 'time_delta';
  $handler->display->display_options['filters']['time_delta']['table'] = 'debugger_traces';
  $handler->display->display_options['filters']['time_delta']['field'] = 'time_delta';
  $handler->display->display_options['filters']['time_delta']['operator'] = '>';
  $handler->display->display_options['filters']['time_delta']['exposed'] = TRUE;
  $handler->display->display_options['filters']['time_delta']['expose']['operator_id'] = 'time_delta_op';
  $handler->display->display_options['filters']['time_delta']['expose']['label'] = 'Time Delta is greater than';
  $handler->display->display_options['filters']['time_delta']['expose']['operator'] = 'time_delta_op';
  $handler->display->display_options['filters']['time_delta']['expose']['identifier'] = 'time_delta';
  /* Filter criterion: Debugger: Traces: Memory delta */
  $handler->display->display_options['filters']['mem_delta']['id'] = 'mem_delta';
  $handler->display->display_options['filters']['mem_delta']['table'] = 'debugger_traces';
  $handler->display->display_options['filters']['mem_delta']['field'] = 'mem_delta';
  $handler->display->display_options['filters']['mem_delta']['operator'] = '>';
  $handler->display->display_options['filters']['mem_delta']['exposed'] = TRUE;
  $handler->display->display_options['filters']['mem_delta']['expose']['operator_id'] = 'mem_delta_op';
  $handler->display->display_options['filters']['mem_delta']['expose']['label'] = 'Memory delta is greater than';
  $handler->display->display_options['filters']['mem_delta']['expose']['operator'] = 'mem_delta_op';
  $handler->display->display_options['filters']['mem_delta']['expose']['identifier'] = 'mem_delta';

  /* Display: Debugger: Traces */
  $handler = $view->new_display('page', 'Debugger: Traces', 'page_1');
  $handler->display->display_options['path'] = 'admin/reports/debugger/traces';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Traces';
  $handler->display->display_options['menu']['weight'] = '0';

  /* Display: Traces by function */
  $handler = $view->new_display('page', 'Traces by function', 'page_2');
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Debugger: Functions: Function name */
  $handler->display->display_options['arguments']['name']['id'] = 'name';
  $handler->display->display_options['arguments']['name']['table'] = 'debugger_functions';
  $handler->display->display_options['arguments']['name']['field'] = 'name';
  $handler->display->display_options['arguments']['name']['relationship'] = 'fncid';
  $handler->display->display_options['arguments']['name']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['name']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['name']['limit'] = '0';
  $handler->display->display_options['path'] = 'admin/reports/debugger/traces/function';

  /* Display: Traces by path */
  $handler = $view->new_display('page', 'Traces by path', 'page_3');
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Debugger: Requests: Path */
  $handler->display->display_options['arguments']['path']['id'] = 'path';
  $handler->display->display_options['arguments']['path']['table'] = 'debugger_requests';
  $handler->display->display_options['arguments']['path']['field'] = 'path';
  $handler->display->display_options['arguments']['path']['relationship'] = 'rid';
  $handler->display->display_options['arguments']['path']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['path']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['path']['limit'] = '0';
  $handler->display->display_options['path'] = 'admin/reports/debugger/traces/path';

  /* Display: Traces as Tree */
  $handler = $view->new_display('page', 'Traces as Tree', 'page_4');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'tree';
  $handler->display->display_options['style_options']['main_field'] = 'tid';
  $handler->display->display_options['style_options']['parent_field'] = 'ptid';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['label'] = 'Header';
  $handler->display->display_options['header']['area']['content'] = 'Use <a href="http://drupal.org/project/views_tree">Views tree</a> to display the debugger traces. Any ideas or features for better looking, please report there. Or <a href="http://drupal.org/node/add/project-issue/debugger">suggest</a> a better visual solution.';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Debugger: Traces: Trace ID */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'debugger_traces';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['exclude'] = TRUE;
  /* Field: Debugger: Traces: Trace ID of parent */
  $handler->display->display_options['fields']['ptid']['id'] = 'ptid';
  $handler->display->display_options['fields']['ptid']['table'] = 'debugger_traces';
  $handler->display->display_options['fields']['ptid']['field'] = 'ptid';
  $handler->display->display_options['fields']['ptid']['exclude'] = TRUE;
  /* Field: Debugger: Functions: Function name */
  $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
  $handler->display->display_options['fields']['name_1']['table'] = 'debugger_functions';
  $handler->display->display_options['fields']['name_1']['field'] = 'name';
  $handler->display->display_options['fields']['name_1']['relationship'] = 'fncid';
  $handler->display->display_options['fields']['name_1']['label'] = 'Function';
  /* Field: Debugger: Functions: Function name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'debugger_functions';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'pfncid';
  $handler->display->display_options['fields']['name']['label'] = 'Function parent';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  /* Field: Debugger: Files: Module */
  $handler->display->display_options['fields']['module']['id'] = 'module';
  $handler->display->display_options['fields']['module']['table'] = 'debugger_files';
  $handler->display->display_options['fields']['module']['field'] = 'module';
  $handler->display->display_options['fields']['module']['relationship'] = 'fid';
  /* Field: Debugger: Traces: Time Delta */
  $handler->display->display_options['fields']['time_delta']['id'] = 'time_delta';
  $handler->display->display_options['fields']['time_delta']['table'] = 'debugger_traces';
  $handler->display->display_options['fields']['time_delta']['field'] = 'time_delta';
  $handler->display->display_options['fields']['time_delta']['label'] = 'Time Delta (ms)';
  $handler->display->display_options['fields']['time_delta']['separator'] = ' ,';
  /* Field: Debugger: Traces: Memory delta */
  $handler->display->display_options['fields']['mem_delta']['id'] = 'mem_delta';
  $handler->display->display_options['fields']['mem_delta']['table'] = 'debugger_traces';
  $handler->display->display_options['fields']['mem_delta']['field'] = 'mem_delta';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  $handler->display->display_options['path'] = 'admin/reports/debugger/traces-tree';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Tree';
  $handler->display->display_options['menu']['weight'] = '0';
  $translatables['debugger_traces'] = array(
    t('Defaults'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Empty data'),
    t('No traces found.'),
    t('Debugger: Request'),
    t('Debugger: File'),
    t('Debugger: Function'),
    t('Debugger: Function Parent'),
    t('Debugger: Function of menu callback'),
    t('Trace ID'),
    t('Trace ID of parent'),
    t('rid'),
    t('Path'),
    t('(front)'),
    t('Function'),
    t('Function parent'),
    t('Module'),
    t('Function ID'),
    t('Function ID of parent'),
    t('File ID'),
    t('File Path'),
    t('Line'),
    t('Request ID'),
    t('Time Delta (ms)'),
    t('.'),
    t(' ,'),
    t('Memory delta'),
    t(','),
    t('Menu callback function'),
    t('(unknown)'),
    t('Router path'),
    t('Time Delta is greater than'),
    t('Memory delta is greater than'),
    t('Debugger: Traces'),
    t('Traces by function'),
    t('All'),
    t('Traces by path'),
    t('Traces as Tree'),
    t('Header'),
    t('Use <a href="http://drupal.org/project/views_tree">Views tree</a> to display the debugger traces. Any ideas or features for better looking, please report there. Or <a href="http://drupal.org/node/add/project-issue/debugger">suggest</a> a better visual solution.'),
  );
  $export['debugger_traces'] = $view;

  return $export;
}
