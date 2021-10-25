<?php
function deputychief_chemical_application_view($form, &$form_state,$serviceid ,$factorytype,$applicationid ,$referenceid){
	
	global $base_root,$base_path,$user,$_SESSION;
	
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/sky-forms.css');
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factorytype);
	$application_id 	= encryption_decryption_fun('decrypt',$applicationid);
	$reference_no 	= encryption_decryption_fun('decrypt',$referenceid);
	$form = array();
	
	$form['header'] = array(
		'#markup' 			=> t('<div class="content"><div class="sky-form"><h3 style="text-align: center;"><b>Application for Approval of Plan</b><p>All inputs are provided by applicant only</p><p>All inputs are to be verified by officials</p></h3>'),
	);
		
   $form['application_preview'] = array(
		'#type' 			=> 'fieldset',
		'#title' 			=> t('Factory Information'),
		'#collapsible' 		=> TRUE, // Added
		'#collapsed' 		=> FALSE,  // Added
  	);
	$form['application_preview']['markup_appplication'] = array(
		'#type' 			=> 'markup',
		'#markup' 			=> get_application_details($service_id,$factory_type_id,$application_id,$reference_no),
  	);	
	$form['serviceid_hidden'] = array(
		 '#type' 			=> 'hidden',
		 '#default_value' 	=> $serviceid
	);	
	$form['factorytype_hidden'] = array(
		 '#type' 			=> 'hidden',
		 '#default_value' 	=> $factorytype
	);	
	$form['applicationid_hidden'] = array(
		 '#type' 			=> 'hidden',
		 '#default_value' 	=> $applicationid
	);	
	$form['reference_no_hidden'] = array(
		 '#type' 			=> 'hidden',
		 '#default_value' 	=> encryption_decryption_fun('encrypt',$reference_no),
	);		  

	$form['application_worker'] = array(
		'#type' 			=> 'fieldset',
		'#title' 			=> t('Workers Information'),
		'#collapsible' 		=> TRUE, // Added
		'#collapsed' 		=> FALSE,  // Added
  	); 
          
    $form['application_worker']['markup_appplication'] = array(
		'#type' 			=> 'markup',
		'#markup' 			=> get_all_worker($service_id,$factory_type_id,$application_id,$reference_no),
		
  	);    
	$form['application_documents'] = array(
		'#type' 			=> 'fieldset',
		'#title' 			=> t('Related Documents'),
		'#collapsible' 		=> TRUE, // Added
		'#collapsed' 		=> FALSE,  // Added
  	); 
          
    $form['application_documents']['markup_appplication'] = array(
		'#type' 			=> 'markup',
		'#markup' 			=> get_uploaded_document_data($service_id,$factory_type_id,$application_id,$reference_no),
		
  	); 
	
    return $form;
        
   }

?>