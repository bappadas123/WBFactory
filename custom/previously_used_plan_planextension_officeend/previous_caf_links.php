<?php
    
    $items['inspector/application-verify/%/%/%/%'] = array(
		//'title'	 =>	'Application Verify',
		'page callback'	 =>	'drupal_get_form',
		'page arguments'	=> array('inspector_application_verify',2,3,4,5),
		'file' 	 => 	'includes/inspector_application_verify.inc',
		'access arguments' 	=>  array('permission_for_inspector'),
	);