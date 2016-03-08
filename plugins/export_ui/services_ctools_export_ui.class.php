<?php

/**
 * @file
 * Export-ui handler for the Services module.
 */

class services_ctools_export_ui extends ctools_export_ui {

  /**
   * Page callback for the resources page.
   */
  function resources_page($js, $input, $item) {
    backdrop_set_title($this->get_page_title('resources', $item));
    return backdrop_get_form('services_edit_form_endpoint_resources', $item);
  }

  /**
   * Page callback for the server page.
   */
  function server_page($js, $input, $item) {
    backdrop_set_title($this->get_page_title('server', $item));
    return backdrop_get_form('services_edit_form_endpoint_server', $item);
  }


  /**
   * Page callback for the authentication page.
   */
  function authentication_page($js, $input, $item) {
    backdrop_set_title($this->get_page_title('authentication', $item));
    return backdrop_get_form('services_edit_form_endpoint_authentication', $item);
  }

  /**
   * Page callback for the resource authentication page.
   */
  function resource_authentication_page($js, $input, $item) {
    backdrop_set_title($this->get_page_title('resource_authentication', $item));
    return backdrop_get_form('services_edit_form_endpoint_resource_authentication', $item);
  }

  // Avoid standard submit of edit form by ctools.
  function edit_save_form($form_state) { }

  function set_item_state($state, $js, $input, $item) {
    ctools_export_set_object_status($item, $state);

    menu_rebuild();
    if (!$js) {
      backdrop_goto(ctools_export_ui_plugin_base_path($this->plugin));
    }
    else {
      return $this->list_page($js, $input);
    }
  }
}

