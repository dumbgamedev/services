<?php

/**
 * @file
 *  Link general system functionalities to services module.
 */

function _system_resource_definition() {
  return array(
    'system' => array(
      'actions' => array(
        'connect' => array(
          'access callback' => 'services_access_menu',
          'help' => 'Returns the details of currently logged in user.',
          'file' => array('type' => 'inc', 'module' => 'services', 'name' => 'resources/system_resource'),
          'callback' => '_system_resource_connect',
        ),
        'get_variable' => array(
          'help'   => 'Returns the value of a system variable using config_get() ).',
          'file' => array('type' => 'inc', 'module' => 'services', 'name' => 'resources/system_resource'),
          'callback' => 'config_get',
          'access arguments' => array('get a system variable'),
          'access arguments append' => FALSE,
          'args' => array(
            array(
              'config_name' => 'config_name',
              'optional' => FALSE,
              'source' => array('data' => 'config_name'),
              'description' => t('The name of the config file where the variable to return is stored.'),
              'type' => 'string',
            ),
            array(
              'name' => 'name',
              'optional' => FALSE,
              'source' => array('data' => 'name'),
              'description' => t('The name of the variable to return.'),
              'type' => 'string',
            ),
          ),
        ),
        'set_variable' => array(
          'help'   => 'Sets the value of a system variable using config_set().',
          'file' => array('type' => 'inc', 'module' => 'services', 'name' => 'resources/system_resource'),
          'callback' => 'config_set',
          'access arguments' => array('set a system variable'),
          'access arguments append' => FALSE,
          'args' => array(
            array(
              'config_name' => 'config_name',
              'optional' => FALSE,
              'source' => array('data' => 'config_name'),
              'description' => t('The name of the config file where the variable should be stored.'),
              'type' => 'string',
            ),
            array(
              'name' => 'name',
              'optional' => FALSE,
              'source' => array('data' => 'name'),
              'description' => t('The name of the variable to set.'),
              'type' => 'string',
            ),
            array(
              'name' => 'value',
              'optional' => FALSE,
              'source' => array('data' => 'value'),
              'description' => t('The value to set.'),
              'type' => 'string',
            ),
          ),
        ),
        'del_variable' => array(
          'help'   => 'Deletes a system variable using config_clear().',
          'file' => array('type' => 'inc', 'module' => 'services', 'name' => 'resources/system_resource'),
          'callback' => '_services_config_clear',
          'access arguments' => array('set a system variable'),
          'access arguments append' => FALSE,
          'args' => array(
            array(
              'config_name' => 'config_name',
              'optional' => FALSE,
              'source' => array('data' => 'config_name'),
              'description' => t('The name of the config file where the variable is stored.'),
              'type' => 'string',
            ),
            array(
              'name' => 'name',
              'optional' => FALSE,
              'source' => array('data' => 'name'),
              'description' => t('The name of the variable to delete.'),
              'type' => 'string',
            ),
          ),
        ),
      ),
    ),
  );
}

/**
 * Clears a config variable by deleting the key from the config file.
 */
function _services_config_clear($config_name, $name) {
  $config = config($config_name);
  $config->clear($name);
  $config->save();
  return $config->get();
}

/**
 * Returns the details of currently logged in user.
 *
 * @return
 *   object with session id, session name and a user object.
 */
function _system_resource_connect() {
  global $user;
  services_remove_user_data($user);

  $return = new stdClass();
  $return->sessid = session_id();
  $return->session_name = session_name();
  $return->user = $user;

  return $return;
}
