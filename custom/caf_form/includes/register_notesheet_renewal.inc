<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function register_notesheet_renewal($form, &$form_state,$serviceid,$factory_typeid,$applicationid,$referenceid,$id) {

	$application_id 	= encryption_decryption_fun('decrypt',$applicationid);
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
	$reference_no 		= encryption_decryption_fun('decrypt',$referenceid);	
	$remark_id 			= encryption_decryption_fun('decrypt',$id);
	$get_fa_cafa        = get_fa_cafa($application_id);
	
	$date_of_amenability	= $get_fa_cafa['date_of_amenability'];
	$pcb_no					= $get_fa_cafa['wbpcb_category_name'];
	$pcb_ref_no				= $get_fa_cafa['wbpcb_reference_no'];
	$pcb_ref_date			= $get_fa_cafa['wbpcb_ref_date'];
	$factory_name			= $get_fa_cafa['factory_name'];
	
	$ending_year 			= fetch_year_asc($application_id,$service_id,$factory_type_id,$reference_no);
	foreach($ending_year as $row){
		$ending_year = $row->calculate_end_year;
	}
	
	$occupier_last				 	= get_occupier_last_slab($application_id,$service_id,$factory_type_id,$reference_no);
	//print_r($occupier);die;
	
	$power_worker_details		= get_renewal_max_power_worker($application_id,$service_id,$factory_type_id,$reference_no);
	//print_r($power_worker_details);die();
	
	//$current_year_power			= get_current_year_power($application_id,$service_id,$factory_type_id,$reference_no,$date_of_amenability);
	//print_r($current_year_power);die;
	
	$worker_details 			= get_worker_data_previous_year($application_id,$service_id,$factory_type_id,$reference_no);

	$worker_data_amenabilty 	= get_worker_data_amenabilty_year($application_id,$service_id,$factory_type_id,$reference_no);

	$is_backlog 			= $get_fa_cafa['is_backlog'];
	if($is_backlog == 1){
		$plan_approval_no = $get_fa_cafa['backlog_plan_approval_no'];
		$plan_approval_date =date('dS M Y', strtotime($get_fa_cafa['backlog_plan_approval_date']));
	}else{
		$plan_approval_no = $get_fa_cafa['factory_plan_approval_number'];
		$plan_approval_date = date('dS M Y', strtotime($get_fa_cafa['modification_date']));
	}
	if($factory_type_id==1){
		$factory_category= 'X';
		$description = "Section 2m(i)";
		}elseif($factory_type_id==2){
			$factory_category= 'Y';
			$description = "Section 2m(ii)";
			}elseif($factory_type_id==3){
				$factory_category= 'Z';
				$description = "Section 85";
				}else{
					$factory_category= '';
					}
					
					
					
	$form	= array();
	$form['serviceid_hidden'] = array(
		 '#type' 	 		=> 'hidden',
		 '#default_value' 	=> $serviceid
	);	
	$form['factorytype_hidden'] = array(
	 		'#type' 	 		=> 'hidden',
	 		'#default_value' 	=> $factory_typeid
	);	   
	$form['referance_no_hidden'] = array(
			 '#type' 	 		=> 'hidden',
			 '#default_value' 	=> $referenceid
	);

	$form['application_id_hidden'] = array(
				'#type' 	 		=> 'hidden',
				'#default_value' 	=> $applicationid
	);
	$form['remark_id_hidden'] = array(
				'#type' 	 		=> 'hidden',
				'#default_value' 	=> $id,
	);
	
	$form['application_notesheet']['markup1']	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class="row">
								<div class="box box-info">
									<div class="box-header with-border">
              							<h3 class="box-title">1.Date of visit:</h3>
			    					</div>
									<div class = "box-body">',
	);
	$form['application_notesheet']['dates'] = array(
        '#prefix' 			=> '<div class="col-md-4 col-xs-12">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(a). Date/Dates of Visit:'),
        '#type' 			=> 'textfield',
		'#attributes' 		=> array('class'=>array('form-control multidate'),'title'=>''),
		'#required' 		=> TRUE,
	 );
	$form['application_notesheet']['markup_end1'] 	= array(
			'#suffix' => '</div></div></div>',
	);
	
	$form['application_notesheet']['markup2']	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class="row">
								<div class="box box-info">
									<div class="box-header with-border">
              							<h3 class="box-title">2.In Case of new of existing factory coming under the purview of the Act:</h3>
			    					</div>
									<div class = "box-body">',
	);
	
	$form['application_notesheet']['factory_starting'] = array(
			'#prefix' 		=> '<div class="col-md-4 col-xs-12"><label class="input">',
			'#suffix' 		=> '</label></div>',
			'#title' 		=> t('(a).Date of Starting:'),
			'#attributes' 	=> array('class'=>array('datepicker_cls'),'title'=>''),
			'#type' 		=> 'textfield',
			//'#required' 	=> TRUE,
    );
	
	$form['application_notesheet']['factory_amenabity_date'] = array(
			'#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="input">',
			'#suffix' 			=> '</label></div>',
			'#title' 			=> t('(b).Date of Amenability'),
			'#type' 			=> 'textfield',
			'#default_value' 	=> !empty($date_of_amenability) ? $date_of_amenability : '',
			'#attributes' 		=> array('class' => array( 'datepicker_cls')),
			'#required' 		=> TRUE,
       
    );
	$form['application_notesheet']['markup_end2'] 	= array(
			'#suffix' => '</div></div></div>',
	);
	
	$form['application_notesheet']['markup3']	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class="row">
								<div class="box box-info">
									<div class="box-header with-border">
              							<h3 class="box-title">3.Incase of an old registration factory crossed/closed down/shifted:</h3>
			    					</div>
									<div class = "box-body">',
	);
	
	$form['application_notesheet']['close_reg_no'] = array(
			'#prefix' 		=> '<div class="row"><div class="col-md-4 col-xs-12"><label class="input">',
			'#suffix' 		=> '</label></div>',
			'#title' 		=> t('(a).Registration No:'),
			'#type' 		=> 'textfield',
		 );
	$form['application_notesheet']['date_restart'] = array(
			'#prefix' 		=> '<div class="col-md-4 col-xs-12" ><label class="input">',
			'#suffix' 		=> '</label></div></div>',
			'#title' 		=> t('(b).Date of Restarting'),
			'#attributes' 	=> array('class'=>array('datepicker_cls'),'title'=>''),
			'#type' 		=> 'textfield',
		);
			 
	$form['application_notesheet']['date_cossed'] = array(
			'#prefix' 		=> '<div class="row"><div class="col-md-4 col-xs-12"><label class="input">',
			'#suffix' 		=> '</label></div>',
			'#title' 		=> t('(c).Date of crossed off/ close down/ shifting'),
			'#type' 		=> 'textfield',
			'#attributes' 	=> array('class'=>array('datepicker_cls'),'title'=>''),
		);
	$form['application_notesheet']['date_shift_amenability'] = array(
			'#prefix' 		=> '<div class="col-md-4 col-xs-12" ><label class="input">',
			'#suffix' 		=> '</label></div></div>',
			'#title' 		=>  t('(d).Date of emenability'),
			'#attributes' 	=>  array('class'=>array('datepicker_cls'),'title'=>''),
			'#type' 		=> 'textfield',
		 );
	
	
	$form['application_notesheet']['markup_end3'] 	= array(
			'#suffix' => '</div></div></div>',
	);
	
	$form['application_notesheet']['markup4']	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class="row">
								<div class="box box-info">
									<div class="box-header with-border">
              							<h3 class="box-title">4.Comments on information furnised relating to owner and Occupier of premises / Factory:</h3>
			    					</div>
									<div class = "box-body">',
	);
	 
	$form['application_notesheet']['display_owner'] = array(
			'#prefix' 		=> '<div class="row"><div class="col-md-4 col-xs-12" ><label class="input">',
			'#suffix' 		=> '</label></div>',
			'#title' 		=>  t('Owner Name'),
			'#attributes' 		=> array('class' => array( '')),
			'#default_value'	=> !empty($get_fa_cafa['owner_name']) ? $get_fa_cafa['owner_name'] : '',
			'#type' 		=> 'textfield',
		 );
	$form['application_notesheet']['display_occupier'] = array(
			'#prefix' 		=> '<div class="col-md-4 col-xs-12" ><label class="input">',
			'#suffix' 		=> '</label></div></div>',
			'#title' 		=>  t('Occuiper Name'),
			'#attributes' 		=> array('class' => array( '')),
			'#default_value'	=> !empty($occupier_last) ? $occupier_last : '',
			'#type' 		=> 'textfield',
		 );	 
	$form['application_notesheet']['owner_comment'] = array(
			'#prefix' 		=> '<div class="row"><div class="col-md-12 col-xs-12" ><label class="input">',
			'#suffix' 		=> '</label></div></div>',
			'#title' 		=>  t('Comments'),
			'#type' 		=> 'textarea',
			'#rows'			=> 5,
			'#cols'			=> 250,
		 );
	
	$form['application_notesheet']['markup_end4'] 	= array(
			'#suffix' => '</div></div></div>',
	);
	
	
	$form['application_notesheet']['markup5']	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class="row">
								<div class="box box-info">
									<div class="box-header with-border">
              							<h3 class="box-title">5. Name/ Names of major products in order of volume of production:</h3>
			    					</div>
									<div class = "box-body">',
	);
	
	$nature_details 	= get_manufacturing($application_id,$service_id,$factory_type_id,$reference_no);
   $form['application_notesheet']['is_generating']= array(
					'#prefix'	=> '<div class="row"><div class="col-xs-12"><table class="table table-bordered"> 
										<tr>
   											<th>Manufacturing Year</th>
     										<th>Nature of manufacturing process</th>
	 									</tr>',
					'#suffix'   => '',
					 '#type'	=> 'markup'
					 );
	$i=0;
	
	foreach ($nature_details  as $data_nature)	{		 
	$form['application_notesheet']['row1'.$i] = array(
				'#type' 	=> 'markup',
				'#markup' 	=>  '<tr>'
		);
						
	 $form['application_notesheet']['service_year'.$i] = array(
				'#type' 	=> 'markup',
				'#prefix' 	=> '<td><div class="col-md-6 col-xs-12">',
				'#suffix' 	=> '</div></td>',
				'#markup' 	=> $data_nature->service_year,
        );
	$form['application_notesheet']['nature_manufacturing'.$i] = array(
				'#type' 	=> 'markup',
				'#prefix' 	=> '<td><div class="col-md-6 col-xs-12">',
				'#suffix' 	=> '</div></td>',
				'#markup' 	=> $data_nature->nature_manufacturing,
        );
	$form['application_notesheet']['end_row1'.$i] = array(
				'#type' 	 	=> 'markup',
				'#markup' 	 	=>  '</tr>'
			);	
	$i++;
	}
	
  	$form['application_notesheet']['nature_table_end'] 	= array(
					'#suffix' => '</table></div></div>',		
			);	
	
	$form['application_notesheet']['markup_end5'] 	= array(
			'#suffix' => '</div></div></div>',
	);
	
	
	$form['application_notesheet']['markup6']	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class="row">
								<div class="box box-info">
									<div class="box-header with-border">
              							<h3 class="box-title">6.Nature and amount of installed power(KW/HP):</h3>
			    					</div>
									<div class = "box-body">',
	);
	
	$form['application_notesheet']['power_install'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-12" ><label class="input">',
			'#suffix' 			=> '</label></div></div>',
			'#title' 			=> t('(a).Installed power'),
			'#type' 			=> 'textfield',
			'#default_value' 	=> $power_worker_details['power'],
			'#attributes' 		=> array('class' => array( '')),
			//'#required' 		=> TRUE,
    ); 
	
	
	$form['application_notesheet']['markup_end6'] 	= array(
			'#suffix' => '</div></div></div>',
	);
	$form['application_notesheet']['markup7']	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class="row">
								<div class="box box-info">
									<div class="box-header with-border">
              							<h3 class="box-title">7.Maximun No. of worker employed on any day during the years preceeding the year of registration:</h3>
			    					</div>
									<div class = "box-body">',
	);
	$form['application_notesheet']['worker'] = array(
			'#prefix' 			=> '<div class="col-md-4 col-xs-12" ><label class="input">',
			'#suffix' 			=> '</label></div>',
			'#title' 			=> t('(a).Number of workers'),
			'#type' 			=> 'textfield',
			'#default_value' 	=> $worker_details,
			'#attributes' 		=> array('class' => array( '')),
			
    ); 
	$form['application_notesheet']['worker_at_amen'] = array(
			'#prefix' 			=> '<div class="col-md-4 col-xs-12" ><label class="input">',
			'#suffix' 			=> '</label></div>',
			'#title' 			=> t('(b).No. of workers on date of amenability'),
			'#type' 			=> 'textfield',
			'#default_value' 	=> $worker_data_amenabilty,
			'#attributes' 		=> array('class' => array( '')),
			
    ); 
	
	$form['application_notesheet']['markup_end7'] 	= array(
			'#suffix' => '</div></div></div>',
	);
	$form['application_notesheet']['markup8']	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class="row">
								<div class="box box-info">
									<div class="box-header with-border">
              							<h3 class="box-title">8.Approval No and Date of site and plans if approved, otherwise comments on confirmity of the site & building to the Act:</h3>
			    					</div>
									<div class = "box-body">',
	);
	$form['application_notesheet']['approval_no'] = array(
			'#prefix' 		=> '<div class="row"><div class="col-md-4 col-xs-12" ><label class="input">',
			'#suffix' 		=> '</label></div>',
			'#title' 		=> t('(a).Approval No'),
			'#type' 		=> 'textfield',
			'#default_value' 	=> $plan_approval_no,
			'#attributes' 		=> array('class' => array( ''),'readonly'=>'readonly'),
			'#required' 		=> TRUE,
    );
	$form['application_notesheet']['approval_no_date'] = array(
			'#prefix' 		=> '<div class="col-md-4 col-xs-12" ><label class="input">',
			'#suffix' 		=> '</label></div>',
			'#title' 		=> t('(b).Date'),
			'#default_value' 	=> $plan_approval_date,
			'#type' 		=> 'textfield',
			'#attributes' 		=> array('class' => array( ''),'readonly'=>'readonly'),
			'#required' 		=> TRUE,
    );
	$form['application_notesheet']['plans_comment'] = array(
			'#prefix' 		=> '<div class="col-md-4 col-xs-12" ><label class="input">',
			'#suffix' 		=> '</label></div></div>',
			'#title' 		=> t('(c).Comments'),
			'#default_value'=>	'',
			'#type' 		=> 'textfield',
    );
	$form['application_notesheet']['markup_end8'] 	= array(
			'#suffix' => '</div></div></div>',
	);
	
	$form['application_notesheet']['markup9']	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class="row">
								<div class="box box-info">
									<div class="box-header with-border">
              							<h3 class="box-title">9: Any other additional comment that the inspector may like to add relation to health hazards and safty, effluent disposal, approval of appropriate authority in respect of storage of inflammable liquids, gases etc. approval form environmental pollution department:</h3>
			    					</div>
									<div class = "box-body">',
	);
	$form['application_notesheet']['category_name'] = array(
	    '#prefix' 		=> '<div class="row"><div class="col-md-4 col-xs-12"><b></b>',
        '#suffix' 		=> '</div>',
		'#title' 		=> t('Category'),
		'#type' 		=> 'textfield',
		'#default_value'=> fetch_catogoryname_wbpcb($pcb_no),
		'#attributes' 	=> array('class' => array( ''),'readonly'=>'readonly'),
		'#required' 		=> TRUE,
	);
	$form['application_notesheet']['category_ref'] = array(
	    '#prefix' 		=> '<div class="col-md-4 col-xs-12">',
        '#suffix' 		=> '</div>',
		'#title' 		=> t('reference Number'),
		'#type' 		=> 'textfield',
		'#default_value'=> !empty($pcb_ref_no)?$pcb_ref_no : '',
		'#attributes' 	=> array('class' => array( ''),'readonly'=>'readonly'),
		
	);
	$form['application_notesheet']['category_date'] = array(
	    '#prefix' 		=> '<div class="col-md-4 col-xs-12">',
        '#suffix' 		=> '</div></div>',
		'#title' 		=> t('Date'),
		'#type' 		=> 'textfield',
		'#default_value'=> !empty($pcb_ref_date)?$pcb_ref_date : '',
		'#attributes' => array('class' => array( ''),'readonly'=>'readonly'),
		
	);
	$form['application_notesheet']['category_comment'] = array(
	    '#prefix' 		=> '<div class="row>"<div class="col-md-12 col-xs-12">',
        '#suffix' 		=> '</div></div>',
		'#title' 		=> t('Comments'),
		'#type' 		=> 'textarea',
		'#rows'			=> 5,
		'#cols'			=> 250,
		'#default_value'=> '',
		'#attributes' => array('class' => array( '')),
		
	);
	$form['application_notesheet']['markup_end9'] 	= array(
			'#suffix' => '</div></div></div>',
	);
	 $value_niccode = isset($form_state['values']['classification_no']) ? $form_state['values']['classification_no'] : $factory_niccode;
    if (!empty($value_niccode)) {
        $query = db_select('nic_2008_code_details', 'code')->fields('code', array('code.sub_class_code'))->condition('code.sub_class_code', trim($value_niccode), '=');
        $result = $query->execute();
		if ($result->rowcount() > 0) {
            $final       	   = $result->fetchAssoc();
         	$value_niccode     = $final['sub_class_code'];
        }
    }
	$form['application_notesheet']['markup10']	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class="row">
								<div class="box box-info">
									<div class="box-header with-border">
              							<h3 class="box-title">10: Recommended for registration under classification:</h3>
			    					</div>
									<div class = "box-body">',
	);
	$form['application_notesheet']['classification_no'] = array(
				'#prefix' 			=> '<div class="row"><div class="col-md-3 col-xs-12"><label class="input">',
				'#suffix' 			=> '</div>',
				'#title' 			=> t('Classification'),
				'#type' 			=> 'textfield',
				'#autocomplete_path' => 'nicautocomplete',
				'#id' 				=> 'niccode_autocomplete',
				'#default_value' 	=> $value_niccode
        );
		
	$form['application_notesheet']['classification_category'] = array(
        '#prefix' 		=> '<div class="col-md-3 col-xs-12" ><label class="input">',
        '#suffix' 		=> '</label></div>',
        '#title' 		=> t('Category'),
		'#type' 		=> 'textfield',
		'#default_value'=> !empty($factory_category) ? $factory_category : '',
		'#attributes' 	=> array('class' => array( ''),'readonly'=>'readonly'),
		'#description'   => '<font color="#FF0000">'.$description.'</font>',
		'#required' 		=> TRUE,
    );
	//echo $date_of_amenability;die;
	if (date('Y-m-d') > $date_of_amenability ){$checked ='old';}else{$checked= 'new';}
	$form['application_notesheet']['category_old_new'] = array(
        '#prefix' 		=> '<div class="col-md-3 col-xs-12" >',
        '#suffix' 		=> '</label></div>',
        '#title' 		=> t('Old/New'),
		'#type' 		=> 'radios',
		'#options' 		=> array('old' => 'Old', 'new' => 'New'),
		'#default_value' => $checked,
    );
	$form['application_notesheet']['amenability'] = array(
        '#prefix' 		=> '<div class="col-md-3 col-xs-12" ><label class="input">',
        '#suffix' 		=> '</label></div></div>',
        '#title' 		=> t('W.e.f Amenability date'),
		'#type' 		=> 'textfield',
		'#default_value'=> !empty($date_of_amenability) ? $date_of_amenability : '',
		'#attributes' 	=> array('class' => array( ''),'readonly'=>'readonly'),
		'#required' 		=> TRUE,
    );
	
	$form['application_notesheet']['hp'] = array(
        '#prefix' 		=> '<div class="row"><div class="col-md-4 col-xs-12" ><label class="input">Grant and issue of license after renewing if for',
        '#suffix' 		=> '</label></div>',
        '#title' 		=> t('power'),
		'#type' 		=> 'textfield',
		'#default_value' 	=> $power_worker_details['max_power'],
		'#attributes' 	=> array('class' => array( '')),
		
    );
	$form['application_notesheet']['worker_year'] = array(
        '#prefix' 		=> '<div class="col-md-4 col-xs-12" ><label class="input">&nbsp;',
        '#suffix' 		=> '</label></div>',
        '#title' 		=> t('workers'),
		'#type' 		=> 'textfield',
		'#default_value' 	=> $power_worker_details['max_worker'],
		'#attributes' 	=> array('class' => array( '')),
    );
	$year_arry = explode("TO", $power_worker_details['service_year']);
	$validupto_year = $year_arry[1];
	$form['application_notesheet']['last_year'] = array(
        '#prefix'		=> '<div class="col-md-4 col-xs-12" ><label class="input">&nbsp;',
        '#suffix' 		=> '</label></div></div>',
		'#type' 		=> 'textfield',
        '#title' 		=> t('valid upto'),
		'#default_value' 	=> $validupto_year,
		'#attributes' 	=> array('class' => array( ''),'readonly'=>'readonly'),
		//'#required' 		=> TRUE,
    );
	$form['application_notesheet']['markup_end10'] 	= array(
			'#suffix' => '</div></div></div>',
	);
	
	$form['application_notesheet']['markup11']	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class="row">
								<div class="box box-info">
									<div class="box-header with-border">
              							<h3 class="box-title">11: E-Note:</h3>
			    					</div>
									<div class = "box-body">',
	);
	
	$form['application_notesheet']['note'] = array(
        '#prefix'		=> '<div class ="row"><div class="col-md-12 col-xs-12" ><label class="textarea">',
        '#suffix' 		=> '</label></div></div>',
		'#type' 		=> 'textarea',
		'#rows'			=> 5,
		'#cols'			=> 250,
        '#title' 		=> t('E-note'),
		//'#required' 	=> TRUE,
    );
	
	$form['submit'] = array(
        '#prefix' 		=> '<div class="row"><div class="col-md-12">',
        '#suffix' 		=> '</div></div>',
        '#attributes' 	=> array('class' => array('btn btn-info')),
        '#type' 		=> 'submit',
        '#value' 		=> 'Send'
	);
	
  	$form['application_notesheet']['markup_end11'] 	= array(
			'#suffix' => '</div></div></div>',
	);
	return	$form;
}

	
function get_occupier_last_slab_display($application_id,$service_id,$factory_type_id,$reference_no){
	global $base_root,$base_path,$user;
	
	$get_all_data = array();
	$type					= '';
	$details				='';
	$address_of_director	='';
	
	$get_all_data = get_occupier_last_slab($application_id,$service_id,$factory_type_id,$reference_no);
	
	$header 		= array(
									
									array('data'=> 'Application Period'),
									array('data'=> 'Details'),
									array('data'=> 'Residential Address'),
									//array('data'=> 'Action'),
								);
	if(!empty($get_all_data)){
		foreach($get_all_data as $details){ 
			$type =$details->type_director;
			$is_occupier =$details->is_occupier;
			if($is_occupier == 1){
				$occupier = '-(Occupier)';
			}
			
		$fieldArr_director			 =  array('district_director','sub_division_director','area_type_director','block_mun_cor_sez_not_director','grm_ward_sector_not_director','police_station_director','pincode_director','state_director','post_office_director');
    $address_of_director	 =	$details->adress_line1_director.'<br>'.get_full_address('fa_director_details','sub-table',$details->id,$fieldArr_director);
	$occupier_deatils	=	$$details->name_director.'<br/>Father/Husband name:-'.$details->father_husband_name_director.'<br/>Age:-'.$$details->age_director.'(Year)';
			$rows[] 	= array( 
					array('data' =>$details->add_year_director ,'class' => array('')),
					array('data' =>$occupier_deatils ,'class' => array('')),
					array('data' =>$address_of_director ,'class' => array('')),	
					//array('data' =>'View' ,'class' => array('')),
				);
		} 
		
	}
	$output = theme_table(
	array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id'=>'', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	).theme('pager');	
		 return $output;
}
	
function register_notesheet_renewal_submit($form, &$form_state){
    global $user;
    $userid = $user->uid;
    $val    = $form_state['values'];
	//print_r($val);die;
	
	$service_id			= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']); 
	$factorytype_id		= 	encryption_decryption_fun('decrypt',$val['factorytype_hidden']);
	$application_id		= 	encryption_decryption_fun('decrypt',$val['application_id_hidden']);
	$reference_no		=  	encryption_decryption_fun('decrypt',$val['referance_no_hidden']);
	$remark_no			=  	encryption_decryption_fun('decrypt',$val['remark_id_hidden']);
	$journal_id			=  	encryption_decryption_fun('decrypt',$val['journal_id']);


	$inspector_notesheet = array(
		'remark_id' 				=> $remark_no,
		'application_no' 			=> $application_id,
		'service_id' 				=> $service_id,
		'factory_type_id' 			=> $factorytype_id,
		'referance_no' 				=> $reference_no,
		
		'dates' 					=> $val['dates'],
		'factory_starting' 			=> $val['factory_starting'],
		'factory_amenabity_date'	=> $val['factory_amenabity_date'],
		'close_reg_no' 				=> $val['close_reg_no'],
		'date_cossed' 				=> $val['date_cossed'],
		'date_restart' 				=> $val['date_restart'],
		'date_shift_amenability'	=> $val['date_shift_amenability'],
		'owner_comment' 			=> $val['owner_comment'],
		
		//'volume_production' 		=> $list,
		'power_install' 			=> $val['power_install'],
		'worker' 					=> $val['worker'],
		'worker_at_amen' 			=> $val['worker_at_amen'],
		
		'approval_no' 				=> $val['approval_no'],
		'approval_no_date' 			=> $val['approval_no_date'],
		'plans_comment'				=> $val['plans_comment'],
		
		'category' 					=> $val['category_name'],
		'category_ref' 				=> $val['category_ref'],
		'category_date' 			=> $val['category_date'],
		'category_comment'			=> $val['category_comment'],
		'category_old_new'			=> $val['category_old_new'],
		
		'classification' 			=> $val['classification_no'],
		'classification_category'	=> $val['classification_category'],
		
		
		'amenability' 				=> $val['amenability'],
		'hp' 						=> $val['hp'],
		'worker_year' 				=> $val['worker_year'],
		'last_year' 				=> $val['last_year'],
		'note' 						=> $val['note'],
		
		'uid' 						=> $userid,
		);	
//print_r($inspector_notesheet);die('ds');
	$id=db_insert('fa_cafa_notesheet')->fields($inspector_notesheet)->execute();
	if(!empty($id)){
		
	$data =	 array('status' => 'DC','remarks'=>'details');		
						$queryabc 		 =	db_update('fa_cafa_remarks');
						$queryabc		 ->	fields($data);
						$queryabc		 ->	condition('id',$remark_no,'=');	
						$queryabc		 ->	execute();
						
	
						
						
	$data =	 array('application_status' => 'DC','classification_no' => $val['classification_no'],'classification_category' => $val['classification_category']);		
						$queryabc 		 =	db_update('fa_cafa');
						$queryabc		 ->	fields($data);
						$queryabc		 ->	condition('id',$application_id,'=');
						$queryabc		 ->	condition('service_id',$service_id,'=');
						$queryabc	     ->	condition('factory_typeid',$factorytype_id,'=');
						$queryabc		 ->	condition('reference_number',$reference_no,'=');		
						$queryabc		 ->	execute();
						
						//-----------Worker table update---------------------------
						$worker_status 	= 	array('worker_registration_status' => 'DC');
						$queryabc 		=	db_update('fa_worker_details');
						$queryabc			->	fields($worker_status);
						$queryabc		    ->	condition('application_id',$application_id,'=');
						$queryabc		    ->	condition('service_id',$service_id,'=');
						$queryabc			->	condition('factory_type',$factorytype_id,'=');
						$queryabc			->	condition('application_reference_no',$reference_no,'=');
						$queryabc			->	execute();
					  //----------------Documents Update-------------------
						$doc_status 	= 	array('application_status' => 'DC');
						$queryabc 		=	db_update('fa_caf_upload_doc');
						$queryabc		->	fields($doc_status);
						$queryabc		->	condition('app_id',$application_id,'=');
						$queryabc		->	condition('upload_documents_service_id',$service_id,'=');
						$queryabc	    ->	condition('upload_doc_factory_type_id',$factorytype_id,'=');
						$queryabc		->	condition('application_reference_no',$reference_no,'=');
						$queryabc		->	execute();
						
					//-----------Manufacturing table update---------------------------
					  $manufacturing_status 	= 	array('manufacturing_application_status' => 'DC');
					  $querymanufacturing 		=	db_update('fa_nature_manufacturing');
					  $querymanufacturing			->	fields($manufacturing_status);
					  $querymanufacturing		    ->	condition('application_id',$application_id,'=');
					  $querymanufacturing		    ->	condition('service_id',$service_id,'=');
					  $querymanufacturing			->	condition('factory_type',$factorytype_id,'=');
					  $querymanufacturing			->	condition('application_reference_no',$reference_no,'=');
					  $querymanufacturing			->	execute();
					  
					  //-----------Power table update---------------------------
					  $power_status 	= 	array('power_application_status' => 'DC');
					  $querypower 		=	db_update('fa_power_details');
					  $querypower			->	fields($power_status);
					  $querypower		    ->	condition('application_id',$application_id,'=');
					  $querypower		    ->	condition('service_id',$service_id,'=');
					  $querypower			->	condition('factory_type',$factorytype_id,'=');
					  $querypower			->	condition('application_reference_no',$reference_no,'=');
					  $querypower			->	execute();
					  
					  //-----------Director table update---------------------------
					  $director_status 	= 	array('application_status' => 'DC');
					  $querydirector 		=	db_update('fa_director_details');
					  $querydirector			->	fields($director_status);
					  $querydirector		    ->	condition('application_director_id',$application_id,'=');
					  $querydirector		    ->	condition('director_service_id',$service_id,'=');
					  $querydirector			->	condition('factory_type_id',$factorytype_id,'=');
					  $querydirector			->	condition('application_reference_no',$reference_no,'=');
					  $querydirector			->	execute();
					  
					  //-----------Manager table update---------------------------
					  $manager_status 	= 	array('application_status' => 'DC');
					  $querymanager 		=	db_update('fa_manager_details');
					  $querymanager			->	fields($manager_status);
					  $querymanager		    ->	condition('application_manager_id',$application_id,'=');
					  $querymanager		    ->	condition('manager_service_id',$service_id,'=');
					  $querymanager			->	condition('factory_type_id',$factorytype_id,'=');
					  $querymanager			->	condition('application_reference_no',$reference_no,'=');
					  $querymanager			->	execute();
					
	drupal_set_message('Your notesheet has been successfully created and forwarded Deputy Director.');
	
	drupal_goto('inspector-renewal/view-renewal-details/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factorytype_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/'.encryption_decryption_fun('encrypt',$remark_no));
	}else{
		drupal_set_message('Your notesheet not created.','error');
		$form_state['rebuild'] = true;
	}
}

function get_renewal_max_power_worker($application_id,$service_id,$factory_type_id,$reference_no){
	$is_tranfer_fees =1;
	//echo $application_id.'---appid<br/>'.$service_id.'----Service id <br/>'.$factory_type_id.'----factory_id <br/>'.$reference_no;die();
	$power_worker_current = db_query("select power,worker,max_power,max_worker,service_year from fa_calculates_license_fees WHERE application_id='".$application_id."' AND service_id='".$service_id."' AND factory_type='".$factory_type_id."' AND application_reference_no='".$reference_no."' AND is_tranfer_fees!='".$is_tranfer_fees."' AND service_year!='' ORDER BY id DESC LIMIT 1;
")->fetchAssoc();
	
	return $power_worker_current;
	}
