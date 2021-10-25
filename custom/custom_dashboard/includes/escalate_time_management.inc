<?php
function escalate_time_management($form, &$form_state) {  
    global $base_root, $base_path;
	
	$form            = array();

    //$plan_section = $factory_inspector = $deputy_director = $joint_director = $chief_inspector = $factory_inspector_dsc = '0';      

        $get_fa_escalate_time       = get_fa_escalate_time();
        //print_r($get_fa_escalate_time);die();
        $total      				= $get_fa_escalate_time['total'];
		$plan_section          		= $get_fa_escalate_time['plan_section'];
		$factory_inspector          = $get_fa_escalate_time['factory_inspector'];
        $deputy_director 		    = $get_fa_escalate_time['deputy_director'];
        $joint_director      		= $get_fa_escalate_time['joint_director'];
        $chief_inspector       		= $get_fa_escalate_time['chief_inspector'];
        $factory_inspector_dsc      = $get_fa_escalate_time['factory_inspector_dsc'];

	/********** Time - Start **********/
    
    $form['header']            	= array(
        '#markup' 				=> t('<div class="row cus-page-outer-view"><div class="content">')
    );
    $form['escalation_time'] 	= array(
        '#type' 				=> 'fieldset',
        '#title' 				=> t(' Total Time'),
        '#collapsible' 			=> TRUE, // Added
        '#collapsed' 			=> FALSE // Added
    );

    $form['escalation_time']['total_title'] = array(
        '#prefix' 				=> '<div class="row"><div class="col-md-6 text-line-42">',
        '#suffix' 				=> '</div>',
        '#type' 				=> 'markup',
        '#markup' 				=> 'Maximum days allowed to process the Application of Approval of Plan'
    );
    $form['escalation_time']['total'] = array(
        '#prefix' 				=> '<div class="col-md-6"><label class="input label-block">',
        '#suffix' 				=> '</label></div></div>',
        '#type' 				=> 'textfield',
        '#default_value' 		=> $total ? $total : '50',
		'#attributes' 			=> array('class' => array('charField')),
		'#maxlength' 			=> 2
    );

    $form['escalation_role_time'] = array(
        '#type' 				=> 'fieldset',
        '#title' 				=> t(' Division Time'),
        '#collapsible' 			=> TRUE, // Added
        '#collapsed' 			=> FALSE // Added
    );

	$form['escalation_role_time']['plan_section_title'] = array(
        '#prefix' 				=> '<div class="row"><div class="col-md-6 text-line-42">',
        '#suffix' 				=> '</div>',
        '#type' 				=> 'markup',
        '#markup' 				=> 'Plan Section ( Receiving )'
    );
    $form['escalation_role_time']['plan_section'] = array(
        '#prefix' 				=> '<div class="col-md-6"><label class="input label-block">',
        '#suffix' 				=> '</label></div></div>',
        '#type' 				=> 'textfield',
        '#default_value' 		=> $plan_section ? $plan_section : '3',
		'#attributes' 			=> array('class' => array('charField', 'plan_section')),
		'#maxlength' 			=> 2
    );

    $form['escalation_role_time']['factory_inspector_title'] = array(
        '#prefix' 				=> '<div class="row"><div class="col-md-6 text-line-42">',
        '#suffix' 				=> '</div>',
        '#type' 				=> 'markup',
        '#markup' 				=> 'Assistant Director of Factories'
    );
    $form['escalation_role_time']['factory_inspector'] = array(
        '#prefix' 				=> '<div class="col-md-6 test"><label class="input label-block">',
        '#suffix' 				=> '</label></div></div>',
        '#type' 				=> 'textfield',
        '#default_value' 		=> $factory_inspector ? $factory_inspector : '22',
		'#attributes' 			=> array('class' => array('charField')),
		'#maxlength' 			=> 2
    );

    $form['escalation_role_time']['deputy_director_title'] = array(
        '#prefix' 				=> '<div class="row"><div class="col-md-6 text-line-42">',
        '#suffix' 				=> '</div>',
        '#type' 				=> 'markup',
        '#markup' 				=> 'Deputy Director of Factories'
    );
    $form['escalation_role_time']['deputy_director'] = array(
        '#prefix' 				=> '<div class="col-md-6 test"><label class="input label-block">',
        '#suffix' 				=> '</label></div></div>',
        '#type' 				=> 'textfield',
        '#default_value' 		=> $deputy_director ? $deputy_director : '12',
		'#attributes' 			=> array('class' => array('charField')),
		'#maxlength' 			=> 2
    );

    $form['escalation_role_time']['joint_director_title'] = array(
        '#prefix' 				=> '<div class="row"><div class="col-md-6 text-line-42">',
        '#suffix' 				=> '</div>',
        '#type' 				=> 'markup',
        '#markup' 				=> 'Joint Director of Factories'
    );
    $form['escalation_role_time']['joint_director'] = array(
        '#prefix' 				=> '<div class="col-md-6"><label class="input label-block">',
        '#suffix' 				=> '</label></div></div>',
        '#type' 				=> 'textfield',
        '#default_value' 		=> $joint_director ? $joint_director : '5',
		'#attributes' 			=> array('class' => array('charField')),
		'#maxlength' 			=> 2
    );

    $form['escalation_role_time']['chief_inspector_title'] = array(
        '#prefix' 				=> '<div class="row"><div class="col-md-6 text-line-42">',
        '#suffix' 				=> '</div>',
        '#type' 				=> 'markup',
        '#markup' 				=> 'Director of Factories'
    );
    $form['escalation_role_time']['chief_inspector'] = array(
        '#prefix' 				=> '<div class="col-md-6"><label class="input label-block">',
        '#suffix' 				=> '</label></div></div>',
        '#type' 				=> 'textfield',
        '#default_value' 		=> $chief_inspector ? $chief_inspector : '5',
		'#attributes' 			=> array('class' => array('charField')),
		'#maxlength' 			=> 2
    );

    $form['escalation_role_time']['factory_inspector_dsc_title'] = array(
        '#prefix' 				=> '<div class="row"><div class="col-md-6 text-line-42">',
        '#suffix' 				=> '</div>',
        '#type' 				=> 'markup',
        '#markup' 				=> 'Assistant Director of Factories (for DSC)'
    );
	$form['escalation_role_time']['factory_inspector_dsc'] = array(
        '#prefix' 				=> '<div class="col-md-6"><label class="input label-block">',
        '#suffix' 				=> '</label></div></div>',
        '#type' 				=> 'textfield',
        '#default_value' 		=> $factory_inspector_dsc ? $factory_inspector_dsc : '3',
		'#attributes' 			=> array('class' => array('charField')),
		'#maxlength' 			=> 2
    );
	
	$form['submit'] = array(
        '#prefix' 				=> '',
        '#suffix' 				=> '</div></div>',
        '#attributes' 			=> array(
            'class' 			=> array(
                'btn btn-dark pull-right'
            )
        ),
        '#type' 				=> 'submit',
        '#value' 				=> 'Save & Continue'
    	);

    return $form;
}

function escalate_time_management_submit($form, &$form_state)
{
    global $user;
    $userid 				= $user->uid;
    $val    				= $form_state['values'];

   $sum_total = $val['plan_section']+$val['factory_inspector']+$val['deputy_director']+$val['joint_director']+$val['chief_inspector']+$val['factory_inspector_dsc'];
   
   if($sum_total != $val['total'])
   {
	  	drupal_set_message('Summation of alloted time should be same as Total time.','error');
		drupal_goto('escalate-time-management');
   } else {
   
	   $get_fa_escalate_time       = get_fa_escalate_time();
	   if(!empty($get_fa_escalate_time)) 
	   { 
		$num_updated = db_update('fa_escalate_time')->fields(array('status' => 0))->execute();
	   } 
	   $escalation_time = array(
			'total'      				=> $val['total'],
			'plan_section'       		=> $val['plan_section'],
			'factory_inspector'         => $val['factory_inspector'],
			'deputy_director' 		    => $val['deputy_director'],
			'joint_director'     		=> $val['joint_director'],
			'chief_inspector'       	=> $val['chief_inspector'],
			'factory_inspector_dsc'     => $val['factory_inspector_dsc'],
			'created_date' 				=> date('Y-m-d')
		);
		
		db_insert('fa_escalate_time')->fields($escalation_time)->execute();
		drupal_set_message('Escalation time has been saved successfully.');
		drupal_goto('escalate-time-management');
	}
}

?>