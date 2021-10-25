<?php
  
  drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
  function decission_form($form, &$form_state){

	  global $user;
	  $uid 						= $user->uid;

	  $form = array();
	  $form['decission_making'] 	= array(
			  '#type'		=> 'markup',
			  '#prefix'	=> '<div class="row"><div class="box box-info"><div class="box-header with-border"><b style="color:red; font-size:20px;">THIS PAGE IS UNDER TESTING PHASE</b> <br>
							  <h3 class="box-title" style="font-size:20px; font-weight:bold;">Questionnaire / Wizard to check eligibility for e-Services</h3>
							  </div><div class = "box-body">',
		  );	
	  
	ctools_include('ajax');
	ctools_include('modal');
	ctools_modal_add_js();	 
	$tt=$base_root.$base_path.'section85/nojs'; 	
	$link_t=ctools_modal_text_button(t('View Process List'), $tt ,t('View Process List')) ;
	
	ctools_include('ajax');
	ctools_include('modal');
	ctools_modal_add_js();	 
	$tc=$base_root.$base_path.'chemical/nojs'; 	
	$link_c=ctools_modal_text_button(t('View Chemical Product List'), $tc ,t('View Chemical Product List')) ;
	
	$establishment_type_options = array('1'=>"New/ Proposed Factory/ Greenfield Project",'2'=>"Registered Factory / Project");	
		$form['decission_making']['factory_establishment_type']= array(
				 '#prefix'	 		=> '<div class="row"><div class="col-xs-6 dec-form-row-height">',
				 '#suffix'    		=>'</div></div><div class="row">',
				 '#type'		 	=> 'radios',
				 '#title'			=>	t('Choose Type of Factory ?'),
				 '#options'   		=> $establishment_type_options,	
				 '#ajax'			=> array(
											 'event' 		=> 'change',
											 'effect' 		=> 'fade',			
											 'callback'		=> 'get_ajax_decission',
											 'progress'		=>	array(
											 'type'			=> 'throbber',
											 'message'		=> t('loading'),
										 )
								 ),
				 '#required'		=> TRUE,
				
		 );
  $value_factory_establishment_type	        = !empty($form_state['values']['factory_establishment_type'])? $form_state['values']['factory_establishment_type'] : '';
  
	$form['decission_making']['markup_details']= array(
			 '#prefix'	 		=> '<div id="markup_message">',
			 '#suffix'    		=> '</div>',
			
		 );
	$form['decission_making']['factory_type_hidden']= array(
			 '#prefix'	 		=> '<div id="factory_type_hidden">',
			 '#suffix'    		=> '</div>',
			
		 );

	if($value_factory_establishment_type == 2)
	{
		$go_dashboard = l('Go to Dashboard','applicant-dashboard', array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
		  $form['decission_making']['markup_details']= array(
					 '#prefix'	 		=> '<div id="markup_message" class="col-xs-12">',
					 '#suffix'    		=> '</div>',
					 '#type'			=>'markup',
					  '#markup'			=> '<span style="color: #FF0000;padding: 3px 10px; display:inline-block;argin-top:34px; border:1px solid;">Find out your factory on the dashboard and apply for any enlisted service <br/> <b>Or</b> please click on ADD REGISTERED FACTORY option on dashboard and add your factory profile and then you can apply for any enlisted service in our portal </font><i class="fa fa-hand-o-right"></i> '.$go_dashboard .'</span>' 
			);
      }
	  
	$form['decission_making']['service_list'] = array(
		'#prefix' 			=> '<div id="service_list_div">',
		'#suffix' 			=> '</div>',
	);
	$form['decission_making']['sub_service_list'] = array(
		'#prefix' 			=> '<div id="sub_service_list_div">',
		'#suffix' 			=> '</div>',
	);
	$form['decission_making']['have_plan_approval_number']= array(
		'#prefix'	 		=> '<div id="have_plan_approval_number_div">',
		'#suffix'    		=> '</div>',
	);
	$form['decission_making']['plan_approvalnumber']= array(
		'#prefix'	 		=> '<div id="plan_approvalnumber_div">',
		'#suffix'    		=>'</div>',
	);	
	$form['decission_making']['plan_approvaldate']= array(
		'#prefix'	 		=> '<div id="plan_approvaldate_div">',
		'#suffix'    		=>'</div>',
	);			  		 
	$form['decission_making']['verify_button']= array(
		'#prefix'	 		=> '<div id="verify_button_div">',
		'#suffix'    		=>'</div>',
	);	
	$form['decission_making']['use_power']= array(
		'#prefix'	 		=> '<div id="use_power_div">',
		'#suffix'    		=>'</div>',
	);
	$form['decission_making']['no_of_workers_y']= array(
		'#prefix'	 		=> '<div id="no_of_workers_y_div">',
		'#suffix'    		=> '</div>',
	); 
	$form['decission_making']['no_of_workers_1']= array(
		'#prefix'	 		=> '<div id="no_of_workers_y_div_1">',
		'#suffix'    		=> '</div>',
	);
	$form['decission_making']['is_chemical']= array(
		'#prefix'	 		=> '<div id="is_chemical_div">',
		'#suffix'    		=>'</div>',
	);
	$form['decission_making']['markup_details_cat']= array(
		'#prefix'	 		=> '<div id="markup_message_cat">',
		'#suffix'    		=> '</div></div>',
	);
	$form['decission_making']['apply_service'] = array(
		'#prefix' 			=> '<div id="apply_service_div">',
		'#suffix' 			=> '</div>',
	);

 if($value_factory_establishment_type == 1){
	$service_list_1 		   	= get_all_master_service();
	$form['decission_making']['service_list'] = array(
			 '#prefix' 			=> '<div id="service_list_div" class="col-xs-6">',
			 '#suffix' 			=> '</div>',
			 '#title'			=> 'Select service',
			 '#type' 			=> 'select',
			 '#required'		=> TRUE,
			 '#attributes' 		=> array('class'=>array('form-control')),
			 '#options' 		=> $service_list_1,
			 '#ajax'			=> array(
										  'event' 		=> 'change',
										  'effect' 		=> 'fade',			
										  'callback'	=> 'get_ajax_decission',
										  'progress'	=>	array(
										  'type'		=> 'throbber',
										  'message'		=>t('loading'),
										  ),
				  )
		  );
		  
		$value_service	        = !empty($form_state['values']['service_list'])? $form_state['values']['service_list'] : '';
		if($value_service == 1) {
			$sub_service_list 		= get_all_sub_service($value_service);
			$form['decission_making']['sub_service_list'] = array(
				 '#prefix' 			=> '<div id="sub_service_list_div" class="col-xs-6">',
				 '#suffix' 			=> '</div>',
				 '#title'			=> 'Select sub-service',
				 '#type' 			=> 'select',
				 '#required'		=> TRUE,
				 '#attributes' 		=> array('class'=>array('form-control')),
				 '#options' 		=> $sub_service_list,
				 '#ajax'			=> array(
										  'event' 		=> 'change',
										  'effect' 		=> 'fade',			
										  'callback'	=> 'get_ajax_decission',
										  'progress'	=>	array(
										  'type'		=> 'throbber',
										  'message'		=>t('loading'),
										  ),
				  )
			  );
		}
		
	$value_subservice	        = !empty($form_state['values']['sub_service_list'])? $form_state['values']['sub_service_list'] : '';	
	
	
	// PLAN SERVICE
	
	if($value_subservice == 4){
		
		$power_options = array('Yes'=>"Yes",'No'=>"No");	
		$form['decission_making']['use_power']= array(
				 '#prefix'	 		=> '<div  id ="use_power_div" class="col-xs-6"">',
				 '#suffix'    		=>'</div>',
				 '#type'		 	=> 'radios',
				 '#title'			=>	t('Does Your Factory Use Power (Electrical / Mechanical / Both) ?'),
				 '#options'   		=> $power_options,	
				 '#ajax'			=> array(
											 'event' 		=> 'change',
											 'effect' 		=> 'fade',			
											 'callback'		=> 'get_ajax_decission',
											 'progress'		=>	array(
											 'type'			=> 'throbber',
											 'message'		=> t('loading'),
										 )
								 ),
				 '#required'		=> TRUE,
				 
		 );
		 
		$value_power	        = !empty($form_state['values']['use_power'])? $form_state['values']['use_power'] : '';	
		$workers_label = 'Workers likely to be employed including contractual workers or staff on any day';
		if($value_power == "Yes"){
			$form['decission_making']['no_of_workers_y']= array(
				 '#prefix'	 		=> '<div id="no_of_workers_y_div"><div class="col-xs-6">',
				 '#suffix'    		=> '</div></div>',
				 '#type'		 	=> 'radios',
				 '#title'			=>	t('Are the number of '.$workers_label.' 10 or more?'),
				 '#options'   		=> array('more10'=>"Yes",'less10'=>"No"),
				 '#ajax'			=> array(
											 'event' 		=> 'change',
											 'effect' 		=> 'fade',			
											 'callback'		=> 'get_ajax_decission',
											 'progress'		=>	array(
											 'type'			=> 'throbber',
											 'message'		=> t('loading'),
										 )
								 ),
				 '#required'		=> TRUE,
			 );
			 $chem_prod = array('Y'=>"Yes",'N'=>"No");	  
		$form['decission_making']['is_chemical']= array(
			 '#prefix'	 		=> '<div id="is_chemical_div"><div class="col-xs-12 dec-form-row-height">',
			 '#suffix'    		=>'</div></div>',
			 '#type'		 	=> 'radios',
			 '#title'			=>	t('Do You Manufacture Any Chemical Product from the given list ? '.$link_c),
			 '#options'   		=> $chem_prod,
			 '#required'		=> TRUE,
		); 
			
		}if($value_power == "No"){
			$form['decission_making']['no_of_workers_y']= array(
				 '#prefix'	 		=> '<div id="no_of_workers_y_div"><div class="col-xs-6">',
				 '#suffix'    		=> '</div></div>',
				 '#type'		 	=> 'radios',
				 '#title'			=>	t('Are the number of '.$workers_label.' 20 or more?'),
				 '#options'   		=> array('more20'=>"Yes",'less20'=>"No"),
				 '#ajax'			=> array(
											 'event' 		=> 'change',
											 'effect' 		=> 'fade',			
											 'callback'		=> 'get_ajax_decission',
											 'progress'		=>	array(
											 'type'			=> 'throbber',
											 'message'		=> t('loading'),
										 )
								 ),
				 '#required'		=> TRUE,
			 );
		}
		
		$value_worker	        = !empty($form_state['values']['no_of_workers_y'])? $form_state['values']['no_of_workers_y'] : '';	
		
		 if($value_power == 'Yes'	 && $value_worker== 'more10'){
			 
		 $form['decission_making']['markup_details_cat']= array(
				 '#prefix'	 		=> '<div id="markup_message_cat"><div class="col-xs-6">',
				 '#suffix'    		=> '</div></div>',
				 '#type'			=>'markup',
				 '#markup'			=> '<span style="background-color: #39B939;color: #fff;padding: 3px 10px; display:inline-block; border-radius: 2px;">Your Factory is categorised under <b>Section 2m(i)</b></span>'
				 );
				 
			$form['decission_making']['factory_type_hidden']= array(
				 '#prefix'	 		=> '<div id="factory_type_hidden">',
				 '#type'			=> 'hidden',
				 '#default_value'	=> '1',
				 '#suffix'    		=> '</div>',
				
			 );
				 
		$form['decission_making']['apply_service'] = array(
				 '#prefix' 			=> '<div class="row"><div id="apply_service_div">',
				 '#suffix' 			=> '</div></div>',
				 '#attributes' 		=> array(
					'class' 			=> array( 'btn btn-dark pull-left' ), 'style' => 'margin:10px 0px 0px 30px;'),
				'#type' 			=> 'submit',
				'#value' 			=> 'APPLY NEW PLAN'
				 
			  );
		 }
		
		if($value_power == 'Yes'	 && $value_worker== 'less10'){
		$form['decission_making']['factory_type_hidden']= array(
				 '#prefix'	 		=> '<div id="factory_type_hidden">',
				 '#type'			=> 'hidden',
				 '#default_value'	=> '3',
				 '#suffix'    		=> '</div>',
				
			 );	
			 
		 $form['decission_making']['markup_details_cat']= array(
				 '#prefix'	 		=> '<div id="markup_message_cat"><div class="col-xs-6">',
				 '#suffix'    		=> '</div></div>',
				 '#type'			=>'markup',
				 '#markup'			=> '<span style="background-color: #39B939;color: #fff;padding: 3px 10px; display:inline-block; border-radius: 2px;">Your Factory is categorised under <b>Section 85.</b> You do not require to apply for Approval of Plan, select other service</span>'
				 );
		
		 }
				
		if($value_power == 'No'	 && $value_worker== 'more20'){
			 
		 $form['decission_making']['markup_details_cat']= array(
				 '#prefix'	 		=> '<div id="markup_message_cat"><div class="col-xs-6">',
				 '#suffix'    		=> '</div></div>',
				 '#type'			=>'markup',
				 '#markup'			=> '<span style="background-color: #39B939;color: #fff;padding: 3px 10px; display:inline-block; border-radius: 2px;">Your Factory is categorised under <b>Section 2m(ii)</b></span>'
				 );
				 $form['decission_making']['factory_type_hidden']= array(
				 '#prefix'	 		=> '<div id="factory_type_hidden">',
				 '#type'			=> 'hidden',
				 '#default_value'	=> '2',
				 '#suffix'    		=> '</div>',
			 );
				 
		$form['decission_making']['apply_service'] = array(
				 '#prefix' 			=> '<div class="row"><div id="apply_service_div">',
				 '#suffix' 			=> '</div></div>',
				 '#attributes' 		=> array(
				 'class' 			=> array( 'btn btn-dark pull-left' ), 'style' => 'margin:10px 0px 0px 30px;'),
				'#type' 			=> 'submit',
				'#value' 			=> 'APPLY NEW PLAN'
				 
			  );
		 }
			
		if($value_power == 'No'	 && $value_worker== 'less20'){
			 
			 $form['decission_making']['factory_type_hidden']= array(
				 '#prefix'	 		=> '<div id="factory_type_hidden">',
				 '#type'			=> 'hidden',
				 '#default_value'	=> '3',
				 '#suffix'    		=> '</div>',
				
			 );
		 $form['decission_making']['markup_details_cat']= array(
				 '#prefix'	 		=> '<div id="markup_message_cat"><div class="col-xs-6">',
				 '#suffix'    		=> '</div></div>',
				 '#type'			=>'markup',
				 '#markup'			=> '<span style="background-color: #39B939;color: #fff;padding: 3px 10px; display:inline-block; border-radius: 2px;">Your Factory is categorised under <b>Section 85.</b> You do not require to apply for Approval of Plan, select other service</span>'
				 );
		 }
	}
	
	// EXTENSION SERVICE
	
	if($value_subservice == 5){

		 $form['decission_making']['plan_approvalnumber']= array(
				 '#prefix'	 		=> '<div id="plan_approvalnumber_div"><div class="col-xs-6">',
				 '#suffix'    		=> '</div></div>',
				 '#type'		 	=> 'textfield',
				 '#title'			=>	t('Plan Approval Number'),
				 '#attributes' 		=> array('class' => array( 'form-control')),
				 '#required'		=> TRUE,
			 );
			 $form['decission_making']['plan_approvaldate']= array(
				 '#prefix'	 		=> '<div id="plan_approvaldate_div"><div class="col-xs-6">',
				 '#suffix'    		=> '</div></div>',
				 '#type'		 	=> 'textfield',
				 '#title'			=>	t('Plan Approval Date'),
				 '#attributes' 		=> array('class' => array( 'form-control datepicker_retify')),
				 '#required'		=> TRUE,
			 );
			 
			$form['decission_making']['verify_button'] = array(
				'#prefix' 			=> '<div id="verify_button_div"><div class="col-xs-6">',
				'#suffix' 			=> '</div></div>',
				'#type' 			=> 'button',
				'#default_value'	=> 'Check E',
				'#attributes' 		=> array('class'=>array('btn-warning'),'style'=>'padding: 4px 14px;border: ;'),
				'#type' 			=> 'button',
				'#ajax'			=> array(
					'event' 		=> 'click',
					'effect' 		=> 'fade',			
					'callback'		=> 'get_ajax_decission',
					'progress'		=>	array(
					'type'			=> 'throbber',
					'message'		=> t('loading'),
					)
					),			  
				);
				
				$value1        = !empty($form_state['values']['plan_approvalnumber'])? $form_state['values']['plan_approvalnumber'] : '';
				$value2        = !empty($form_state['values']['plan_approvaldate'])? $form_state['values']['plan_approvaldate'] : '';
				$result          = get_plan_approval_no($value1,$value2);

				if(!empty($value1) && !empty($value2) && !empty($result)) {
					
				
					$form['decission_making']['verify_button'] = array(
						'#prefix' 			=> '<div id="verify_button_div">',
						'#suffix' 			=> '</div>',
					);


				   $go_dashboard = l('Go to Dashboard','applicant-dashboard', array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));

				   $form['decission_making']['markup_details_cat']= array(
						 '#prefix' 			=> '<div id="markup_message_cat" class="col-xs-6"><span style="color: #FF0000;padding: 3px 10px; display:inline-block;argin-top:34px; border:1px solid;">Find out your factory from dashboard and apply for Registration </font><i class="fa fa-hand-o-right"></i> '.$go_dashboard .'</span>',
						 '#suffix' 			=> '</div>',
					);
				  
				} else if(!empty($value1) && !empty($value2) && empty($result)) { 
				
				   $form['decission_making']['markup_details_cat']= array(
						 '#prefix' 			=> '<div id="markup_message_cat" class="col-xs-12"><span style="color: #FF0000;padding: 3px 10px; display:inline-block;argin-top:34px; border:1px solid;"><b>Either</b> You have provided wrong combination of Plan approval No and Date <b>OR</b> your Factory is not enlisted in our record. Please answer following questions to enlist your factory</span>',
						 '#suffix' 			=> '</div>',
					);
			
				$form['decission_making']['verify_button'] = array(
					'#prefix' 			=> '<div id="verify_button_div">',
					'#suffix' 			=> '</div>',
					);
						
				$power_options = array('Yes'=>"Yes",'No'=>"No");	
				$form['decission_making']['use_power']= array(
						 '#prefix'	 		=> '<div  id ="use_power_div" class="col-xs-6"">',
						 '#suffix'    		=>'</div>',
						 '#type'		 	=> 'radios',
						 '#title'			=>	t('Does Your Factory Use Power (Electrical / Mechanical / Both) ?'),
						 '#options'   		=> $power_options,	
						 '#ajax'			=> array(
													 'event' 		=> 'change',
													 'effect' 		=> 'fade',			
													 'callback'		=> 'get_ajax_decission',
													 'progress'		=>	array(
													 'type'			=> 'throbber',
													 'message'		=> t('loading'),
												 )
										 ),
						 '#required'		=> TRUE,
						 
				 );
				 
				 $value_power	        = !empty($form_state['values']['use_power'])? $form_state['values']['use_power'] : '';	
				 $workers_label = 'Workers likely to be employed including contractual workers or staff on any day';
		
			if($value_power == "Yes")
			{
				   $form['decission_making']['markup_details_cat']= array(
						 '#prefix' 			=> '<div id="markup_message_cat">',
						 '#suffix' 			=> '</div>',
					);

				$form['decission_making']['no_of_workers_y']= array(
					 '#prefix'	 		=> '<div id="no_of_workers_y_div"><div class="col-xs-6">',
					 '#suffix'    		=> '</div></div>',
					 '#type'		 	=> 'radios',
					 '#title'			=>	t('Are the number of '.$workers_label.' 10 or more?'),
					 '#options'   		=> array('more10'=>"Yes",'less10'=>"No"),
					 '#ajax'			=> array(
												 'event' 		=> 'change',
												 'effect' 		=> 'fade',			
												 'callback'		=> 'get_ajax_decission',
												 'progress'		=>	array(
												 'type'			=> 'throbber',
												 'message'		=> t('loading'),
											 )
									 ),
					 '#required'		=> TRUE,
				 );
				 
				$chem_prod = array('Y'=>"Yes",'N'=>"No");	  
				$form['decission_making']['is_chemical']= array(
					 '#prefix'	 		=> '<div id="is_chemical_div"><div class="col-xs-12 dec-form-row-height">',
					 '#suffix'    		=>'</div></div>',
					 '#type'		 	=> 'radios',
					 '#title'			=>	t('Do You Manufacture Any Chemical Product from the given list ? '.$link_c),
					 '#options'   		=> $chem_prod,
					 '#required'		=> TRUE,
				); 
			}
		
			if($value_power == "No")
			{
 			    $form['decission_making']['markup_details_cat']= array(
					 '#prefix' 			=> '<div id="markup_message_cat">',
					 '#suffix' 			=> '</div>',
				);
				$form['decission_making']['no_of_workers_y']= array(
					 '#prefix'	 		=> '<div id="no_of_workers_y_div"><div class="col-xs-6">',
					 '#suffix'    		=> '</div></div>',
					 '#type'		 	=> 'radios',
					 '#title'			=>	t('Are the number of '.$workers_label.' 20 or more?'),
					 '#options'   		=> array('more20'=>"Yes",'less20'=>"No"),
					 '#ajax'			=> array(
												 'event' 		=> 'change',
												 'effect' 		=> 'fade',			
												 'callback'		=> 'get_ajax_decission',
												 'progress'		=>	array(
												 'type'			=> 'throbber',
												 'message'		=> t('loading'),
											 )
									 ),
					 '#required'		=> TRUE,
				 );
			}
		
		 $value_worker	        = !empty($form_state['values']['no_of_workers_y'])? $form_state['values']['no_of_workers_y'] : '';	
		
		 if($value_power == 'Yes'	 && $value_worker== 'more10')
		 {
			 
			 $form['decission_making']['markup_details_cat']= array(
				 '#prefix'	 		=> '<div id="markup_message_cat"><div class="col-xs-6">',
				 '#suffix'    		=> '</div></div>',
				 '#type'			=>'markup',
				 '#markup'			=> '<span style="background-color: #39B939;color: #fff;padding: 3px 10px; display:inline-block; border-radius: 2px;">Your Factory is categorised under <b>Section 2m(i)</b></span>'
				 );
				 
			$form['decission_making']['factory_type_hidden']= array(
				 '#prefix'	 		=> '<div id="factory_type_hidden">',
				 '#type'			=> 'hidden',
				 '#default_value'	=> '1',
				 '#suffix'    		=> '</div>',
				
			 );
				 
			$form['decission_making']['apply_service'] = array(
				 '#prefix' 			=> '<div class="row"><div id="apply_service_div">',
				 '#suffix' 			=> '</div></div>',
				 '#attributes' 		=> array(
				 'class' 			=> array( 'btn btn-dark pull-left' ), 'style' => 'margin:10px 0px 0px 30px;'),
				'#type' 			=> 'submit',
				'#value' 			=> 'APPLY EXTENSION'
				 
			  );
		 }

		
		if($value_power == 'Yes'	 && $value_worker== 'less10')
		{

			 $form['decission_making']['markup_details_cat']= array(
				 '#prefix'	 		=> '<div id="markup_message_cat"><div class="col-xs-6">',
				 '#suffix'    		=> '</div></div>',
				 '#type'			=>'markup',
				 '#markup'			=> '<span style="background-color: #39B939;color: #fff;padding: 3px 10px; display:inline-block; border-radius: 2px;">Your Factory is categorised under <b>Section 85.</b>You dont have Approval of Plan</span>'
				 );
	
	
			$form['decission_making']['factory_type_hidden']= array(
				 '#prefix'	 		=> '<div id="factory_type_hidden">',
				 '#type'			=> 'hidden',
				 '#default_value'	=> '3',
				 '#suffix'    		=> '</div>',
				
			 );	
		 }
				
		if($value_power == 'No'	 && $value_worker== 'more20')
		{

			 $form['decission_making']['markup_details_cat']= array(
					 '#prefix'	 		=> '<div id="markup_message_cat"><div class="col-xs-6">',
					 '#suffix'    		=> '</div></div>',
					 '#type'			=>'markup',
					 '#markup'			=> '<span style="background-color: #39B939;color: #fff;padding: 3px 10px; display:inline-block; border-radius: 2px;">Your Factory is categorised under <b>Section 2m(ii)</b></span>'
					 );
					 $form['decission_making']['factory_type_hidden']= array(
					 '#prefix'	 		=> '<div id="factory_type_hidden">',
					 '#type'			=> 'hidden',
					 '#default_value'	=> '2',
					 '#suffix'    		=> '</div>',
			 );
				 
			$form['decission_making']['apply_service'] = array(
					 '#prefix' 			=> '<div class="row"><div id="apply_service_div">',
					 '#suffix' 			=> '</div></div>',
					 '#attributes' 		=> array(
					 'class' 			=> array( 'btn btn-dark pull-left' ), 'style' => 'margin:10px 0px 0px 30px;'),
					'#type' 			=> 'submit',
					'#value' 			=> 'APPLY EXTENSION'
			  );
		 }
			
		if($value_power == 'No'	 && $value_worker== 'less20')
		{
			 
			$form['decission_making']['markup_details_cat']= array(
				 '#prefix'	 		=> '<div id="markup_message_cat"><div class="col-xs-6">',
				 '#suffix'    		=> '</div></div>',
				 '#type'			=>'markup',
				 '#markup'			=> '<span style="background-color: #39B939;color: #fff;padding: 3px 10px; display:inline-block; border-radius: 2px;">Your Factory is categorised under <b>Section 85.</b> You dont have any Approval of Plan</span>'
			);

			 $form['decission_making']['factory_type_hidden']= array(
				 '#prefix'	 		=> '<div id="factory_type_hidden">',
				 '#type'			=> 'hidden',
				 '#default_value'	=> '3',
				 '#suffix'    		=> '</div>',
			 );
		 }
		}
	}
	
	// REGISTRATION SERVICE
	
	if($value_service == 2) {

		$form['decission_making']['have_plan_approval_number']= array(
			 '#prefix'	 		=> '<div id="have_plan_approval_number_div" class="col-xs-6">',
			 '#suffix'    		=> '</div>',
			 '#type'		 	=> 'radios',
			 '#title'			=>	t('Do you have Plan approval number ?'),
			 '#options'   		=> array('Y'=>"Yes",'N'=>"No"),	
			 '#ajax'			=> array(
										 'event' 		=> 'change',
										 'effect' 		=> 'fade',			
										 'callback'		=> 'get_ajax_decission',
										 'progress'		=>	array(
										 'type'			=> 'throbber',
										 'message'		=> t('loading'),
									 )
							 ),
			 '#required'		=> TRUE,
		);
		
		 $value_have_plan        = !empty($form_state['values']['have_plan_approval_number'])? $form_state['values']['have_plan_approval_number'] : '';

		 if($value_have_plan == 'Y')
		 {

		 	$form['decission_making']['plan_approvalnumber']= array(
				 '#prefix'	 		=> '<div id="plan_approvalnumber_div"><div class="col-xs-6">',
				 '#suffix'    		=> '</div></div>',
				 '#type'		 	=> 'textfield',
				 '#title'			=>	t('Plan Approval Number'),
				 '#attributes' 		=> array('class' => array( 'form-control')),
				 '#required'		=> TRUE,
			 );
			 $form['decission_making']['plan_approvaldate']= array(
				 '#prefix'	 		=> '<div id="plan_approvaldate_div"><div class="col-xs-6">',
				 '#suffix'    		=> '</div></div>',
				 '#type'		 	=> 'textfield',
				 '#title'			=>	t('Plan Approval Date'),
				 '#attributes' 		=> array('class' => array( 'form-control datepicker_retify')),
				 '#required'		=> TRUE,
			 );
			 
			$form['decission_making']['verify_button'] = array(
				'#prefix' 			=> '<div id="verify_button_div"><div class="col-xs-6">',
				'#suffix' 			=> '</div></div>',
				'#type' 			=> 'button',
				'#default_value'	=> 'Check',
				'#attributes' 		=> array('class'=>array('btn-warning'),'style'=>'margin-top:36px;padding: 4px 14px;border: ;'),
				'#type' 			=> 'button',
				'#ajax'			=> array(
					'event' 		=> 'click',
					'effect' 		=> 'fade',			
					'callback'		=> 'get_ajax_decission',
					'progress'		=>	array(
					'type'			=> 'throbber',
					'message'		=> t('loading'),
					)
					),			  
				);
				

					   $value1        = !empty($form_state['values']['plan_approvalnumber'])? $form_state['values']['plan_approvalnumber'] : '';
					   $value2        = !empty($form_state['values']['plan_approvaldate'])? $form_state['values']['plan_approvaldate'] : '';
					 $result          = get_plan_approval_no($value1,$value2);

				if(!empty($value1) && !empty($value2) && !empty($result)){
					
	$go_dashboard = l('Go to Dashboard','applicant-dashboard', array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));

				   $form['decission_making']['markup_details_cat']= array(
						 '#prefix' 			=> '<div id="markup_message_cat" class="col-xs-6"><span style="color: #FF0000;padding: 3px 10px; display:inline-block;argin-top:34px; border:1px solid;">Find out your factory from dashboard and apply for Registration </font><i class="fa fa-hand-o-right"></i> '.$go_dashboard .'</span>',
						 '#suffix' 			=> '</div>',
					);
				  
				} else if(!empty($value1) && !empty($value2) && empty($result)) { 
				
				   $form['decission_making']['markup_details_cat']= array(
						 '#prefix' 			=> '<div id="markup_message_cat" class="col-xs-12"><span style="color: #FF0000;padding: 3px 10px; display:inline-block;argin-top:34px; border:1px solid;"><b>Either</b> You have provided wrong combination of Plan approval No and Date <b>OR</b> your Factory is not enlisted in our record. Please answer following questions to enlist your factory</span>',
						 '#suffix' 			=> '</div>',
					);
			
					$form['decission_making']['verify_button'] = array(
						'#prefix' 			=> '<div id="verify_button_div">',
						'#suffix' 			=> '</div>',
					);
					
					$power_options = array('Yes'=>"Yes",'No'=>"No");	
					$form['decission_making']['use_power']= array(
							 '#prefix'	 		=> '<div  id ="use_power_div" class="col-xs-6"">',
							 '#suffix'    		=>'</div>',
							 '#type'		 	=> 'radios',
							 '#title'			=>	t('Does Your Factory Use Power (Electrical / Mechanical / Both) ?'),
							 '#options'   		=> $power_options,	
							 '#ajax'			=> array(
														 'event' 		=> 'change',
														 'effect' 		=> 'fade',			
														 'callback'		=> 'get_ajax_decission',
														 'progress'		=>	array(
														 'type'			=> 'throbber',
														 'message'		=> t('loading'),
													 )
											 ),
							 '#required'		=> TRUE,
							 
					 );
					 $value_power	        = !empty($form_state['values']['use_power'])? $form_state['values']['use_power'] : '';	
					 $workers_label = 'Workers likely to be employed including contractual workers or staff on any day';
					 
						 if($value_power == "Yes")
						 {
							$form['decission_making']['markup_details_cat']= array(
								 '#prefix' 			=> '<div id="markup_message_cat">',
								 '#suffix' 			=> '</div>',
							);
							$form['decission_making']['no_of_workers_y']= array(
								 '#prefix'	 		=> '<div id="no_of_workers_y_div"><div class="col-xs-6">',
								 '#suffix'    		=> '</div></div>',
								 '#type'		 	=> 'radios',
								 '#title'			=>	t('Are the number of '.$workers_label.' 10 or more?'),
								 '#options'   		=> array('more10'=>"Yes",'less10'=>"No"),
								 '#ajax'			=> array(
															 'event' 		=> 'change',
															 'effect' 		=> 'fade',			
															 'callback'		=> 'get_ajax_decission',
															 'progress'		=>	array(
															 'type'			=> 'throbber',
															 'message'		=> t('loading'),
														 )
												 ),
								 '#required'		=> TRUE,
							 );
							 $chem_prod = array('Y'=>"Yes",'N'=>"No");	  
							$form['decission_making']['is_chemical']= array(
								 '#prefix'	 		=> '<div id="is_chemical_div"><div class="col-xs-12 dec-form-row-height">',
								 '#suffix'    		=>'</div></div>',
								 '#type'		 	=> 'radios',
								 '#title'			=>	t('Do You Manufacture Any Chemical Product from the given list ? '.$link_c),
								 '#options'   		=> $chem_prod,
								 '#required'		=> TRUE,
							); 
						 }
					
					if($value_power == "No")
					{
							
						$form['decission_making']['markup_details_cat']= array(
							 '#prefix' 			=> '<div id="markup_message_cat">',
							 '#suffix' 			=> '</div>',
						);
			
						$form['decission_making']['no_of_workers_y']= array(
							 '#prefix'	 		=> '<div id="no_of_workers_y_div"><div class="col-xs-6">',
							 '#suffix'    		=> '</div></div>',
							 '#type'		 	=> 'radios',
							 '#title'			=>	t('Are the number of '.$workers_label.' 20 or more?'),
							 '#options'   		=> array('more20'=>"Yes",'less20'=>"No"),
							 '#ajax'			=> array(
														 'event' 		=> 'change',
														 'effect' 		=> 'fade',			
														 'callback'		=> 'get_ajax_decission',
														 'progress'		=>	array(
														 'type'			=> 'throbber',
														 'message'		=> t('loading'),
													 )
											 ),
							 '#required'		=> TRUE,
						 );
					}
					
					 $value_worker	        = !empty($form_state['values']['no_of_workers_y'])? $form_state['values']['no_of_workers_y'] : '';	
					
					 if($value_power == 'Yes'	 && $value_worker== 'more10')
					 {
						 
						$form['decission_making']['markup_details_cat']= array(
							 '#prefix'	 		=> '<div id="markup_message_cat"><div class="col-xs-6">',
							 '#suffix'    		=> '</div></div>',
							 '#type'			=>'markup',
							 '#markup'			=> '<span style="background-color: #39B939;color: #fff;padding: 3px 10px; display:inline-block; border-radius: 2px;">Your Factory is categorised under <b>Section 2m(i)</b></span>'
							 );
							 
						$form['decission_making']['factory_type_hidden']= array(
							 '#prefix'	 		=> '<div id="factory_type_hidden">',
							 '#type'			=> 'hidden',
							 '#default_value'	=> '1',
							 '#suffix'    		=> '</div>',
							
						 );
							 
						$form['decission_making']['apply_service'] = array(
							 '#prefix' 			=> '<div class="row"><div id="apply_service_div">',
							 '#suffix' 			=> '</div></div>',
							 '#attributes' 		=> array(
							 'class' 			=> array( 'btn btn-dark pull-left' ), 'style' => 'margin:10px 0px 0px 30px;'),
							'#type' 			=> 'submit',
							'#value' 			=> 'APPLY NEW REGISTRATION'
							 
						  );
					 }
					
					if($value_power == 'Yes'	 && $value_worker== 'less10')
					{
						$form['decission_making']['markup_details_cat']= array(
							 '#prefix'	 		=> '<div id="markup_message_cat"><div class="col-xs-6">',
							 '#suffix'    		=> '</div></div>',
							 '#type'			=>'markup',
							 '#markup'			=> '<span style="background-color: #39B939;color: #fff;padding: 3px 10px; display:inline-block; border-radius: 2px;">Your Factory is categorised under <b>Section 85</b></span>'
							 );
						
						
						$form['decission_making']['factory_type_hidden']= array(
							 '#prefix'	 		=> '<div id="factory_type_hidden">',
							 '#type'			=> 'hidden',
							 '#default_value'	=> '3',
							 '#suffix'    		=> '</div>',
							
						 );	
						 
							 
						$form['decission_making']['apply_service'] = array(
							 '#prefix' 			=> '<div class="row"><div id="apply_service_div">',
							 '#suffix' 			=> '</div></div>',
							 '#attributes' 		=> array(
							 'class' 			=> array( 'btn btn-dark pull-left' ), 'style' => 'margin:10px 0px 0px 30px;'),
							'#type' 			=> 'submit',
							'#value' 			=> 'APPLY NEW REGISTRATION'
							 
						  );
					 }
							
					if($value_power == 'No'	 && $value_worker== 'more20')
					{
						 
						$form['decission_making']['markup_details_cat']= array(
							 '#prefix'	 		=> '<div id="markup_message_cat"><div class="col-xs-6">',
							 '#suffix'    		=> '</div></div>',
							 '#type'			=>'markup',
							 '#markup'			=> '<span style="background-color: #39B939;color: #fff;padding: 3px 10px; display:inline-block; border-radius: 2px;">Your Factory is categorised under <b>Section 2m(ii)</b></span>'
							 );
							 $form['decission_making']['factory_type_hidden']= array(
							 '#prefix'	 		=> '<div id="factory_type_hidden">',
							 '#type'			=> 'hidden',
							 '#default_value'	=> '2',
							 '#suffix'    		=> '</div>',
						);
						 
						$form['decission_making']['apply_service'] = array(
							'#prefix' 			=> '<div class="row"><div id="apply_service_div">',
							'#suffix' 			=> '</div></div>',
							'#attributes' 		=> array(
								'class' 			=> array( 'btn btn-dark pull-left' ), 'style' => 'margin:10px 0px 0px 30px;'),
							'#type' 			=> 'submit',
							'#value' 			=> 'APPLY NEW REGISTRATION'
						);
					 }
						
					if($value_power == 'No'	 && $value_worker== 'less20')
					{
						 
						$form['decission_making']['markup_details_cat']= array(
							 '#prefix'	 		=> '<div id="markup_message_cat"><div class="col-xs-6">',
							 '#suffix'    		=> '</div></div>',
							 '#type'			=>'markup',
							 '#markup'			=> '<span style="background-color: #39B939;color: #fff;padding: 3px 10px; display:inline-block; border-radius: 2px;">Your Factory is categorised under <b>Section 85</b></span>'
						 );
						
						$form['decission_making']['factory_type_hidden']= array(
							 '#prefix'	 		=> '<div id="factory_type_hidden">',
							 '#type'			=> 'hidden',
							 '#default_value'	=> '3',
							 '#suffix'    		=> '</div>',
						);
						
						$form['decission_making']['apply_service'] = array(
							 '#prefix' 			=> '<div class="row"><div id="apply_service_div">',
							 '#suffix' 			=> '</div></div>',
							 '#attributes' 		=> array(
							 'class' 			=> array( 'btn btn-dark pull-left' ), 'style' => 'margin:10px 0px 0px 30px;'),
							'#type' 			=> 'submit',
							'#value' 			=> 'APPLY NEW REGISTRATION'
						);
					 
					 }

				}

		 } else if($value_have_plan == 'N') {
			   $form['decission_making']['markup_details_cat']= array(
					 '#prefix' 			=> '<div id="markup_message_cat" class="col-xs-6"><span style="color: #FF0000;padding: 3px 10px; display:inline-block;argin-top:34px; border:1px solid;"><b>Note :: </b>You do not have Plan approval no. Please apply for Approval of Plan to take more services</span>',
					 '#suffix' 			=> '</div>',
				);
		 }
	
	  }
	
  }
	  return $form;
}
  
 function get_ajax_decission($form, $form_state){
	  
	  $commands = array();
 
	$commands[] = ajax_command_replace('#markup_message', drupal_render($form['decission_making']['markup_details']));
	$commands[] = ajax_command_replace('#service_list_div', drupal_render($form['decission_making']['service_list']));
	$commands[] = ajax_command_replace('#apply_service_div', drupal_render($form['decission_making']['apply_service']));
	$commands[] = ajax_command_replace('#sub_service_list_div', drupal_render($form['decission_making']['sub_service_list']));
	$commands[] = ajax_command_replace('#use_power_div', drupal_render($form['decission_making']['use_power']));
	
	$commands[] = ajax_command_replace('#markup_message_cat', drupal_render($form['decission_making']['markup_details_cat']));
	$commands[] = ajax_command_replace('#no_of_workers_y_div', drupal_render($form['decission_making']['no_of_workers_y']));
	$commands[] = ajax_command_replace('#no_of_workers_y_div_1', drupal_render($form['decission_making']['no_of_workers_1']));
	
	$commands[] = ajax_command_replace('#is_chemical_div', drupal_render($form['decission_making']['is_chemical']));
	$commands[] = ajax_command_replace('#have_plan_approval_number_div', drupal_render($form['decission_making']['have_plan_approval_number']));
	
	$commands[] = ajax_command_replace('#factory_type_hidden', drupal_render($form['decission_making']['factory_type_hidden']));
	$commands[] = ajax_command_replace('#plan_approvalnumber_div', drupal_render($form['decission_making']['plan_approvalnumber']));
	$commands[] = ajax_command_replace('#plan_approvaldate_div', drupal_render($form['decission_making']['plan_approvaldate']));
	$commands[] = ajax_command_replace('#verify_button_div', drupal_render($form['decission_making']['verify_button']));

	  return array('#type' => 'ajax', '#commands' => $commands);
  }  
  
 /*function verify_planapproval_number($form, &$form_state){
	
	global $base_root,$base_path,$user;
	 $commands = array();
	$uid 							= $user->uid;
	$val   							= $form_state['values'];
	 $plan_approvaldate				= $val['plan_approvaldate'];
	 $plan_approvalnumber				= $val['plan_approvalnumber'];
	$verify_flag = get_plan_approval_no($plan_approvalnumber, $plan_approvaldate);
	$form['verify_flag_hidden']['#default_value'] = 'I HATE chickens';
	//$form_state['values']['verify_flag_hidden'][LANGUAGE_NONE][0]['value'] = $verify_flag;
	//$form['verify_flag_hidden']['#parents'] = array('verify_flag_hidden'); 
//form_set_value($form['verify_flag_hidden'], array(LANGUAGE_NONE => array(0 => array('value' => 'WORKS'))), $form_state);

//form_set_value($form['verify_flag_hidden'], array('und' => array(0 => array('value' => 'WORKS'))), $form_state);

 //$form_state['values']['verify_flag_hidden']['und'][0]['nid']=378;
print_r($val);
 //$form_state['rebuild'] = true;
 //$form_state['values']['verify_flag_hidden']['und'][0]['entity']->field_fc_other_race['und'][0]['value']="XXX Race set in rules";print_r($val);
//   $form_state['values']['verify_flag_hidden']['und'][0]['nid']=378;
	} */
	
 function decission_form_submit($form, &$form_state){
	
	global $base_root,$base_path,$user;
	$uid 							= $user->uid;
	$val   							= $form_state['values']; //print_r($val); 
	
	$apply_service =$val['apply_service'];
	$factory_type_hidden= $val['factory_type_hidden'];
	$is_chemical	= isset($val['is_chemical']) ? $val['is_chemical'] : 'N';
	
	if($apply_service=="APPLY NEW PLAN"){
		$decission_service_id_vlue = $val['sub_service_list'];
		$plan_approval_number = NULL;
		$plan_approval_date = NULL;
		$serviceflag = encryption_decryption_fun('encrypt',$apply_service.'-'.$is_chemical);
		
		 drupal_goto('applicant/factory-parta-forongoingservice/'.encryption_decryption_fun('encrypt',$decission_service_id_vlue).'/'.encryption_decryption_fun('encrypt',$factory_type_hidden).'/'.encryption_decryption_fun('encrypt',$plan_approval_number).'/'.encryption_decryption_fun('encrypt',$plan_approval_date).'/'.$serviceflag) ;
	}
	
	if($apply_service=="APPLY NEW REGISTRATION"){
		$decission_service_id_vlue = $val['service_list'];
		$plan_approval_number = $val['plan_approvalnumber'];
		$plan_approval_date = $val['plan_approvaldate'];
		$serviceflag = encryption_decryption_fun('encrypt',$apply_service.'-'.$is_chemical);
		
			  $get_details = get_plan_approval_no($plan_approval_number, $plan_approval_date); //echo "re";print_r($get_details);die;
			  
			   $given_date = $plan_approval_date;
				$given_year = date('Y', strtotime($given_date));
			
				$fetch_date = !empty($get_details['plan_approval_date']) ? $get_details['plan_approval_date'] : $get_details['backlog_plan_approval_date'];
				$fetch_year = date('Y', strtotime($fetch_date));

			 if($given_year == $fetch_year)
			 {
				 if(strtotime($given_date) == strtotime($fetch_date))
				 {
					 drupal_set_message('This factory <b>('.$get_details['factory_name'].')</b> is already exists. Either you can find it from your dashboard or this factory does not belongs to you. Please apply Registration from your dashboad','success');
					drupal_goto('/applicant-dashboard') ;
				 } 
			 } else {		 
		 			drupal_goto('applicant/factory-parta-forongoingservice/'.encryption_decryption_fun('encrypt',$decission_service_id_vlue).'/'.encryption_decryption_fun('encrypt',$factory_type_hidden).'/'.encryption_decryption_fun('encrypt',$plan_approval_number).'/'.encryption_decryption_fun('encrypt',$plan_approval_date).'/'.$serviceflag) ;
			 } 

	}

	if($apply_service=="APPLY EXTENSION")
	{
		$decission_service_id_vlue = $val['sub_service_list'];
		$plan_approval_number = $val['plan_approvalnumber'];
	    $plan_approval_date = $val['plan_approvaldate'];
		$serviceflag = encryption_decryption_fun('encrypt',$apply_service.'-'.$is_chemical);
			  
			  $get_details = get_plan_approval_no($plan_approval_number, $plan_approval_date); //echo "re";print_r($get_details);die;
			  
			     $given_date = $plan_approval_date;
				 $given_year = date('Y', strtotime($given_date));
			
				$fetch_date = !empty($get_details['plan_approval_date']) ? $get_details['plan_approval_date'] : $get_details['backlog_plan_approval_date'];
				$fetch_year = date('Y', strtotime($fetch_date));

			 if($given_year == $fetch_year)
			 {
				 if(strtotime($given_date) == strtotime($fetch_date))
				 {
					 drupal_set_message('This factory <b>('.$get_details['factory_name'].')</b> is already exists. Either you can find it from your dashboard or this factory does not belongs to you. Please apply Registration from your dashboad','success');
					drupal_goto('/applicant-dashboard') ;
				 } 
			 } else {		 
		        drupal_goto('applicant/factory-parta-forongoingservice/'.encryption_decryption_fun('encrypt',$decission_service_id_vlue).'/'.encryption_decryption_fun('encrypt',$factory_type_hidden).'/'.encryption_decryption_fun('encrypt',$plan_approval_number).'/'.encryption_decryption_fun('encrypt',$plan_approval_date).'/'.$serviceflag) ;
			 } 
		  
	}
} 
