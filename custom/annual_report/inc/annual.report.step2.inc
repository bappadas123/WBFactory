<?php

function annual_report_step2( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;
	 
	
	 
	    $filenumber=encryption_decryption_fun('decrypt',$filenumber);
	 
	
	      
	
	    $step2_select_query = db_select('labour_factory_statcell_annual_report_t2_a', 'a');
       
        $step2_select_query->condition('a.annual_inspection_id',trim($filenumber),'=');
      
		
        $step2_select_query->fields('a',array('ado_no_of_accidents_fatal','ado_no_of_accidents_serious','ado_no_danger_occur_explosion','ado_no_danger_occur_fire','ado_no_danger_occur_gassing','ado_no_danger_occur_toxic_release','ado_no_danger_occur_collapse','ado_no_danger_occur_others','ado_no_visit_paid_fatal_accidents','ado_no_visit_paid_serious_accidents','ado_no_visit_paid_explosion','ado_no_visit_paid_fire','ado_no_visit_paid_gassing','ado_no_visit_paid_toxic_release','ado_no_visit_paid_collapse','ado_no_visit_paid_others'));
        $step2_select_query_result = $step2_select_query->execute(); 
		
		$result_step2=$step2_select_query_result->fetchAssoc();
		$ado_no_of_accidents_fatal=$result_step2['ado_no_of_accidents_fatal'];
        $ado_no_of_accidents_serious=$result_step2['ado_no_of_accidents_serious'];
        $ado_no_danger_occur_fire=$result_step2['ado_no_danger_occur_fire'];
         $ado_no_danger_occur_explosion=$result_step2['ado_no_danger_occur_explosion'];
        $ado_no_danger_occur_gassing=$result_step2['ado_no_danger_occur_gassing'];
		
		$ado_no_danger_occur_toxic_release=$result_step2['ado_no_danger_occur_toxic_release'];
		$ado_no_danger_occur_collapse=$result_step2['ado_no_danger_occur_collapse'];

		$ado_no_danger_occur_others=$result_step2['ado_no_danger_occur_others'];


	   $ado_no_visit_paid_fatal_accidents=$result_step2['ado_no_visit_paid_fatal_accidents'];
       $ado_no_visit_paid_serious_accidents=$result_step2['ado_no_visit_paid_serious_accidents'];
	   $ado_no_visit_paid_explosion=$result_step2['ado_no_visit_paid_explosion'];
	   $ado_no_visit_paid_fire=$result_step2['ado_no_visit_paid_fire'];
	   $ado_no_visit_paid_gassing=$result_step2['ado_no_visit_paid_gassing'];
	   $ado_no_visit_paid_toxic_release=$result_step2['ado_no_visit_paid_toxic_release'];
	   $ado_no_visit_paid_collapse=$result_step2['ado_no_visit_paid_collapse'];
	   $ado_no_visit_paid_others=$result_step2['ado_no_visit_paid_others'];
	
		
	

		
    
	   $mr_istquery = db_select('labour_factory_statcell_annual_report', 'a');
       
        $mr_istquery->condition('a.annual_inspection_id',trim($filenumber),'=');
      
    
        $mr_istquery->fields('a',array('area','inspector_id', 'report_from_date','report_to_date'));
        $mr_istquery_result = $mr_istquery->execute(); 
    
       $result_mrist=$mr_istquery_result->fetchAssoc();
       $area=$result_mrist['area'];
       $inspector_id=$result_mrist['inspector_id'];
       $inspector_name=get_name($inspector_id);
       $report_from_date=date('d-m-Y', strtotime($result_mrist['report_from_date']));
      $report_to_date=date('d-m-Y', strtotime($result_mrist['report_to_date']));
	      
	
	
	// Part A
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
     drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
		
	      $form['step2Afield'] = array(
          '#title' => t('<b>  Area:'.$area.' , From date: '.$report_from_date.' , To date: '.$report_to_date.'  </b>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 

          $form['step2Afield']['inspectionid'] = 
	    array('#type' => 'hidden',  
	    '#value' => $filenumber,
	   
	   );

		
     	
$form['step2Afield']['colA1'] = array
              (
		       '#prefix' => '<div class="table-panel-header"><b>2(A) Accident and Dangerous occurrences </b> </div>
			   <div class="table-responsive">
			   <table class="table table-striped table-bordered table-responsive admin-custom-table">
			   <thead>
			   <tr><th colspan="2" >', 
		       '#markup'=>'<b> Accidents  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );


                $form['step2Afield']['colA2'] = array
              (
		       '#prefix' => ' <th colspan="6"  >', 
		        '#markup'=>'<b> Dangerous Occurrenccs  </b>',
           

		        '#suffix'=>'</th></tr></thead>',
	   
	   
           ); 


               $form['step2Afield']['colA3'] = array
              (
		       '#prefix' => '<tr> <td   >', 
		        '#markup'=>'<b> Fatal  </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


               $form['step2Afield']['colA4'] = array
              (
		       '#prefix' => ' <td   >', 
		        '#markup'=>'<b> Serious </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

               $form['step2Afield']['colA5'] = array
              (
		       '#prefix' => ' <td   >', 
		        '#markup'=>'<b> Explosion </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

              $form['step2Afield']['colA6'] = array
              (
		       '#prefix' => ' <td  >', 
		        '#markup'=>'<b> Fire </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

              $form['step2Afield']['colA7'] = array
              (
		       '#prefix' => ' <td  >', 
		        '#markup'=>'<b> Gassing </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


                $form['step2Afield']['colA8'] = array
              (
		       '#prefix' => '  <td  >', 
		        '#markup'=>'<b> Toxic release </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

                $form['step2Afield']['colA9'] = array
              (
		       '#prefix' => '  <td  >', 
		        '#markup'=>'<b> Collapse </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 
                $form['step2Afield']['colA10'] = array
              (
		       '#prefix' => '  <td  >', 
		        '#markup'=>'<b> Others </b>',
           

		        '#suffix'=>'</td></tr>',
	   
	   
           ); 
             

      
           $form['step2Afield']['colA3val'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		         '#default_value' =>$ado_no_of_accidents_fatal
	   
	   
           ); 


           $form['step2Afield']['colA4val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		          '#default_value' =>$ado_no_of_accidents_serious
	   
	   
           ); 
               $form['step2Afield']['colA5val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		          '#default_value' =>$ado_no_danger_occur_fire
	   
	   
           ); 
               $form['step2Afield']['colA6val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		      '#default_value' =>$ado_no_danger_occur_explosion
	   
	   
           ); 
               $form['step2Afield']['colA7val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		         '#default_value' =>$ado_no_danger_occur_gassing
	   
	   
           ); 

               $form['step2Afield']['colA8val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		           '#default_value' =>$ado_no_danger_occur_toxic_release
	   
	   
           ); 

               $form['step2Afield']['colA9val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		               '#default_value' =>$ado_no_danger_occur_collapse
	   
	   
           ); 
               $form['step2Afield']['colA10val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		       '#suffix'=>'</td></tr>',
		       '#default_value' =>$ado_no_danger_occur_others
	   
	   
           ); 
               
                 $form['step2Afield']['colA11'] = array
              (
		       '#prefix' => ' <tr> <th colspan="7"  >', 
		        '#markup'=>'<b> No. of visits paid in connection with </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


                 $form['step2Afield']['colA12'] = array
              (
		       '#prefix' => '  <td   >', 
		        '#markup'=>'<b> Others </b>',
           

		        '#suffix'=>'</td></tr>',
	   
	   
           ); 

            $form['step2Afield']['colA13'] = array
              (
		       '#prefix' => ' <tr> <td   >', 
		        '#markup'=>'<b> Fatal </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           );

           $form['step2Afield']['colA14'] = array
              (
		       '#prefix' => '  <td   >', 
		        '#markup'=>'<b> Serious </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           );

            $form['step2Afield']['colA15'] = array
              (
		       '#prefix' => '  <td   >', 
		        '#markup'=>'<b> Explosion </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           );

            $form['step2Afield']['colA16'] = array
              (
		       '#prefix' => '  <td   >', 
		        '#markup'=>'<b> Fire </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           );

            $form['step2Afield']['colA17'] = array
              (
		       '#prefix' => '  <td   >', 
		        '#markup'=>'<b> Gassing </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           );

            $form['step2Afield']['colA18'] = array
              (
		       '#prefix' => '  <td   >', 
		        '#markup'=>'<b> Toxic release </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           );

            $form['step2Afield']['colA19'] = array
              (
		       '#prefix' => '  <td   >', 
		        '#markup'=>'<b> Collapse </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           );


            $form['step2Afield']['colA20'] = array
              (
		       '#prefix' => '  <td   >', 
		        '#markup'=>'<b> (accident to machinery or plant etc.) </b>',
           

		        '#suffix'=>'</td></tr>',
	   
	   
           );

            $form['step2Afield']['colA13val'] = array
              (
		       '#prefix' => ' <tr><td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		          '#default_value' =>$ado_no_visit_paid_fatal_accidents
	   
	   
           ); 

           $form['step2Afield']['colA14val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		            '#default_value' =>$ado_no_visit_paid_serious_accidents
	   
	   
           ); 

            $form['step2Afield']['colA15val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	       '#default_value' =>$ado_no_visit_paid_explosion
	   
           ); 

            $form['step2Afield']['colA16val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		         '#default_value' =>$ado_no_visit_paid_fire
	   
	   
           ); 

            $form['step2Afield']['colA17val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	            '#default_value' =>$ado_no_visit_paid_gassing
	   
           ); 

           $form['step2Afield']['colA18val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	        '#default_value' =>$ado_no_visit_paid_toxic_release
	   
           ); 

           $form['step2Afield']['colA19val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	        '#default_value' =>$ado_no_visit_paid_collapse
	   
           ); 

            $form['step2Afield']['colA20val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td></tr></table></div>',
		           '#default_value' =>$ado_no_visit_paid_others
	   
	   
           ); 
$form['step2Afield']['submit_button_one']					= array(
																 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
																'#type'					=>'submit',
																'#value'				=>t(' Save '),
																// '#submit' => array('annual_report_step2_save'),
																'#submit' => array('step2_parta_save'),
																 
																);


       //part B

        $form['step2Bfield'] = array(
         '#title' => t(''),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 

          $form['step2Bfield']['colB1'] = array
              (
		       '#prefix' => '<div class="table-panel-header"><b>2(B) Details of Accidents(Fatal/Serious)</b> </div>
			   <div class="table-responsive">
			   <table class="table table-striped table-bordered table-responsive admin-custom-table">
			   <thead>
			   <tr><th width="10%">', 
		       '#markup'=>'<b> Fatal / Serious  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );

            $form['step2Bfield']['colB2'] = array
              (
		       '#prefix' => '<th >', 
		       '#markup'=>'<b> Name Of Factory(R/UR)  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );

            $form['step2Bfield']['colB3'] = array
              (
		       '#prefix' => '<th>', 
		       '#markup'=>'<b> Address of the factories(R/UR)  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );

            $form['step2Bfield']['colB4'] = array
              (
		       '#prefix' => '<th>', 
		       '#markup'=>'<b> Name of injured/deceased persons  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );

           $form['step2Bfield']['colB5'] = array
              (
		       '#prefix' => '<th>', 
		       '#markup'=>'<b> Date of Occurrence  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );


            $form['step2Bfield']['colB6'] = array
              (
		       '#prefix' => '<th>', 
		       '#markup'=>'<b> Date of Expiry  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );

            $form['step2Bfield']['colB7'] = array
              (
		       '#prefix' => '<th>', 
		       '#markup'=>'<b> Infringement Section/Rule Violated  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );

            $form['step2Bfield']['colB8'] = array
              (
		       '#prefix' => '<th>', 
		       '#markup'=>'<b> Classification  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );

            $form['step2Bfield']['colB9'] = array
              (
		       '#prefix' => '<th>', 
		       '#markup'=>'<b> Legal Action Taken(Case No.)  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );

            $form['step2Bfield']['colB10'] = array
              (
		       '#prefix' => '<th>', 
		       '#markup'=>'<b> Remarks  </b>',

		          '#suffix'=>'</th></tr></thead>',
	   
	   
           );

           

              $form['step2Bfield']['colB1val'] = array(
		  
         '#type' => 'radios',
         //'#title' => t('Title Given:   '),
      //  '#required' => TRUE,
         '#options' => array(
         'Fatal' => t('Fatal'),
         'Serious' => t('Serious'),
		  //'Other' => t('Other'),
         ),
		 //'#default_value' =>$area,
	  '#prefix' => '<tr> <td  >',
      
	 '#suffix'=>'</td>',
		 
         );




           $form['step2Bfield']['colB2val'] = array
              (
		       '#prefix' => ' <td  >', 
		          '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 5,

		        '#suffix'=>'</td>',
	   
	   
           ); 

           $form['step2Bfield']['colB3val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 5,

		        '#suffix'=>'</td>',
	   
	   
           ); 

           $form['step2Bfield']['colB4val'] = array
              (
		       '#prefix' => ' <td  >', 
		         '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 5,

		        '#suffix'=>'</td>',
	   
	   
           ); 

           $form['step2Bfield']['colB5val'] = array
              (
		       '#prefix' => ' <td  >', 
		    

              '#type' => 'textfield',
	  
	    // '#attributes' 		=> array('class'=>array('form-control  datepicker_retify'), 'id'=>'per_workers_service_since_work_id_1'),
		  '#attributes' => array('class' => array('datepicker_retify')),

		        '#suffix'=>'</td>',
				   '#size' => 10,
	   
	   
           ); 

           $form['step2Bfield']['colB6val'] = array
              (
		       '#prefix' => ' <td  >', 
		       
		  '#type' => 'textfield',
		 // '#attributes' 		=> array('class'=>array('form-control  datepicker_retify'), 'id'=>'per_workers_service_since_work_id_2'),
		  '#attributes' => array('class' => array('datepicker_retify')),

		        '#suffix'=>'</td>',
				  '#size' => 50,
	   
	   
           ); 

           $form['step2Bfield']['colB7val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 5,

		        '#suffix'=>'</td>',
	   
	   
           ); 

            

           

        $default_vilg='0';
	    $options_classification = array(0 => " Select  ") + an_classification_option();

          $form['step2Bfield']['colB8val'] = array(
	    '#prefix' => ' <td  >', 
        '#suffix'=>'</td>',
		// '#attributes' => array('class' => array('select-estab-shop')),
        '#type' => 'select',
      //  '#title' => ' GP / Ward',
		//'#element_validate' => array('inspection_district_validate'),
        '#options' => $options_classification,
       // '#default_value' => isset($form_state['values']['inspection_dropdown_forth']) ? $form_state['values']['inspection_dropdown_forth'] : $worker_vill_word ,
	   '#default_value' =>  $default_vilg ,
		
		
    ); 


 $form['step2Bfield']['colB9val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );





            $form['step2Bfield']['colB10val'] = array
              (
		       '#prefix' => ' <td  >', 
		         '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 5,

		        '#suffix'=>'</td></tr></table></div>',
	   
	   
           ); 

              	$form['step2Bfield']['submit_button']					= array(
																 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
																	'#type' => 'button',
		                                                           '#event' => 'click',

																 '#default_value' => 'ADD Accidents Details  ',
                                                              '#ajax' => array(
                                                              'callback' => 'add_step2_partb_data',
                                                              'wrapper' => 'step2_part2_div',
                                                                'method' => 'html',
                                                                     'effect' => 'fade'
                                                               )
																);



       $output1='';
      if(trim($filenumber)){
      $query_tab_1_c=db_query('select  *  from labour_factory_statcell_annual_report_t2_b a, labour_factory_accident_classification_mst b where  CAST (a.classification_code AS INTEGER)=b.accident_classification_id and annual_inspection_id = :anid', array(':anid' => trim($filenumber) ));
      if($query_tab_1_c->rowCount() > 0) 
              { 
     $output1 = "<div class='table-responsive'><table class='table table-striped table-bordered table-responsive admin-custom-table add-employee-table-view'>
	 <thead>
	    <tr > <th >Fatal / Serious</th>
      
       <th > Name Of Factory(R/UR)</th>
	    <th >Address of the factories(R/UR)</th>
       
		 <th >Name of injured/deceased persons</th>

		 <th >Date of Occurrence</th>
       
		 <th >Date of Expiry</th>
		  <th >Infringement Section/Rule Violated</th>
       
		 <th >Classification</th>
		  <th >Legal Action Taken(Case No.)</th>
		   <th >Remarks</th>
		   <th >EDIT</th>
		 <th >DELETE</th>
		</tr></thead>";  
			  $i=0;
		foreach($query_tab_1_c as $squan) {
			$i++;
		      $row_id = $squan->row_id; 
		      $annual_inspection_id = $squan->annual_inspection_id; 
	          $accident_type=$squan->accident_type;
			  $acc_det_name_of_factory=$squan->acc_det_name_of_factory;
			  $acc_det_address_of_factory=$squan->acc_det_address_of_factory;
              $acc_det_name_of_deceased_injured=$squan->acc_det_name_of_deceased_injured;

              //$acc_det_date_of_accident=$val['acc_det_date_of_accident']['year'].'-'.$val['acc_det_date_of_accident']['month'].'-'.$val['acc_det_date_of_accident']['day'];

            //$acc_det_expiry=$val['acc_det_expiry']['year'].'-'.$val['acc_det_expiry']['month'].'-'.$val['acc_det_expiry']['day'];
             $acc_det_section_violation=trim($squan->acc_det_section_violation);
              $classification_code=$squan->classification_code;
              $acc_det_action_case_no=$squan->acc_det_action_case_no;
              $remarks=$squan->remarks;
              
              $acc_det_expiry = !empty(trim($squan->acc_det_expiry)) ? date('d-m-Y', strtotime($squan->acc_det_expiry)) : '';
              
			

			   $bb=$base_root.$base_path.'admin/annual-report-tab2-partb-del/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
		    // $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
		       $del_preper=l(t('Delete'),$bb ,array('html'=>TRUE)) ;


                ctools_include('ajax');
                ctools_include('modal');
	            ctools_modal_add_js();	

		        $ed=$base_root.$base_path.'admin/annual-report/step2-edit/nojs/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
		    // $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
		       //$ed_partb_link=l(t('Edit'),$ed ,array('html'=>TRUE)) ;


               	
			$ed_partb_link=ctools_modal_text_button(t('Edit'), $ed ,t('Edit')) ;	





		
		
		     
			  
			  
			  
              if($i%2==0){
		        $output1 .= "<tr>";
				 }
				else
				{
				$output1 .= "<tr>";
				}
				//$output1.= "<td>".$i."</td>"; 
				$output1.= "<td>".$accident_type."</td>";
			    $output1.= "<td>".$acc_det_name_of_factory."</td>";
                $output1.= "<td>".$acc_det_address_of_factory."</td>";
                $output1.= "<td>".$acc_det_name_of_deceased_injured."</td>";
                $output1.= "<td>".date('d-m-Y', strtotime($squan->acc_det_date_of_accident))."</td>";
                $output1.= "<td>".$acc_det_expiry."</td>";
             
                $output1.= "<td>".$acc_det_section_violation."</td>";
                $output1.= "<td>".$squan->classification_details."</td>";
                $output1.= "<td >".$acc_det_action_case_no."</td>";
				
				$output1.= "<td >".$remarks."</td>";
				$output1.= "<td >".$ed_partb_link."</td>";
				$output1.= "<td >".$del_preper."</td>";
			
              
			   $output1 .= "</tr>";
	          }
              $output1 .= "</table></div>";
			  
			

	
	   }
	}
	 $form['step2Bfield']['prpersonlista'] = array(
	 	'#prefix' => '<div align="left" id="step2_part2_div">'.$output1,
		'#suffix' => '</div>',
       
	);



            //part C

        $form['step2Cfield'] = array(
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 

          $form['step2Cfield']['colC1'] = array
              (
		       '#prefix' => '<div class="table-panel-header"><b>2(C) Details of Dangerous Occurrences</b></div><div class="table-responsive">
		   <table class="table table-striped table-bordered table-responsive admin-custom-table">
		   <thead>
		   <tr><th >', 
		       '#markup'=>'<b> Name of the Factory (R/UR)  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );

            $form['step2Cfield']['colC2'] = array
              (
		       '#prefix' => '<th >', 
		       '#markup'=>'<b> Address of the Factory  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );

            $form['step2Cfield']['colC3'] = array
              (
		       '#prefix' => '<th >', 
		       '#markup'=>'<b> Date and hour of occurrence  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );

            $form['step2Cfield']['colC4'] = array
              (
		       '#prefix' => '<th>', 
		       '#markup'=>'<b> Description of the incident  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );

           $form['step2Cfield']['colC5'] = array
              (
		       '#prefix' => '<th>', 
		       '#markup'=>'<b> No. of persons involved  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );


            $form['step2Cfield']['colC6'] = array
              (
		       '#prefix' => '<th>', 
		       '#markup'=>'<b> Legal Action taken (with case no.)  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );

            $form['step2Cfield']['colC7'] = array
              (
		       '#prefix' => '<th>', 
		       '#markup'=>'<b> Remarks  </b>',

		          '#suffix'=>'</td></th></thead>',
	   
	   
           );

            

            $form['step2Cfield']['colC1val'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		      '#type' => 'textarea',
              '#rows' => 5,
              '#cols' => 5,

		        '#suffix'=>'</td>',
	   
	   
           ); 

           $form['step2Cfield']['colC2val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textarea',
              '#rows' => 5,
              '#cols' => 5,

		        '#suffix'=>'</td>',
	   
	   
           ); 

           $form['step2Cfield']['colC3val'] = array
              (
		       '#prefix' => ' <td  >', 
		     

               '#type' => 'textfield',
                '#size' => 2,

		       // '#suffix'=>'</td>',

		     //  '#attributes' 		=> array('class'=>array('form-control  datepicker_retify'), 'id'=>'daily_wages_service_since_work_id'),
			  '#attributes' => array('class' => array('datepicker_retify')),
	   
	   
           ); 

               $form['step2Cfield']['colC3Timeval'] = array
              (
		       //'#prefix' => ' <td  >', 
		     
                '#type' => 'textfield',
                '#size' => 2,

		        '#suffix'=>'</td>',
		        '#maxlength' =>5,
	   
	   
           ); 

           $form['step2Cfield']['colC4val'] = array
              (
		       '#prefix' => ' <td  >', 
		        '#type' => 'textarea',
                '#rows' => 5,
                 '#cols' => 5,

		        '#suffix'=>'</td>',
	   
	   
           ); 

           $form['step2Cfield']['colC5val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           ); 

           $form['step2Cfield']['colC6val'] = array
              (
		       '#prefix' => ' <td  >', 
		        '#type' => 'textarea',
              '#rows' => 5,
              '#cols' => 5,

		        '#suffix'=>'</td>',
	   
	   
           ); 

           $form['step2Cfield']['colC7val'] = array
              (
		       '#prefix' => '<td>', 
		        '#type' => 'textarea',
              '#rows' => 5,
              '#cols' => 5,

		        '#suffix'=>'</td></tr></table></div>',
	   
	   
           ); 

           
$form['step2Cfield']['submit_button']					= array(
																 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
																	'#type' => 'button',
		                                                           '#event' => 'click',

																 '#default_value' => 'ADD Dangerous Occurrences  ',
                                                              '#ajax' => array(
                                                              'callback' => 'add_step2_partc_data',
                                                              'wrapper' => 'step2_part3_div',
                                                                'method' => 'html',
                                                                     'effect' => 'fade'
                                                               )
																);



  $output2='';
      if(trim($filenumber)){
      $query_tab_2_c=db_query('select  *  from labour_factory_statcell_annual_report_t2_c where  annual_inspection_id = :anid', array(':anid' => trim($filenumber) ));
      if($query_tab_2_c->rowCount() > 0) 
              { 
     $output2 = "<div class='table-responsive'>
		   <table class='table table-striped table-bordered table-responsive admin-custom-table add-employee-table-view'>
		   <thead>
	    <tr > <th >Name of the Factory (R/UR)</th>
      
       <th > Address of the Factory</th>
	    <th >Date and hour of occurrence</th>
       
		 <th >Description of the incident</th>

		 <th >No. of persons involved</th>
       
		 <th >Legal Action taken (with case no.)</th>
		  <th >Remarks</th>
       
		 
		 <th >DELETE</th>
		</tr></thead>";  
			  $i=0;
		foreach($query_tab_2_c as $squan) {
			$i++;
		      $row_id = $squan->row_id; 
		      $annual_inspection_id = $squan->annual_inspection_id; 
	          $factory_name=$squan->factory_name;
			  $factory_address=$squan->factory_address;
			  $date_time=$squan->date_time;
              $desc_incident=$squan->desc_incident;

              //$acc_det_date_of_accident=$val['acc_det_date_of_accident']['year'].'-'.$val['acc_det_date_of_accident']['month'].'-'.$val['acc_det_date_of_accident']['day'];

            //$acc_det_expiry=$val['acc_det_expiry']['year'].'-'.$val['acc_det_expiry']['month'].'-'.$val['acc_det_expiry']['day'];
             $no_person=$squan->no_person;
              $legal_action=$squan->legal_action;
              $remarks=$squan->remarks;
             
              
              
			

			   $bb=$base_root.$base_path.'admin/annual-report-tab2-partc-del/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
		
		      $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
		
		
		
		      $del_preper=l(t('Delete'),$bb ,array('html'=>TRUE)) ;
			  
			  
			  
              if($i%2==0){
		        $output2 .= "<tr>";
				 }
				else
				{
				$output2 .= "<tr>";
				}
				//$output1.= "<td>".$i."</td>"; 
				$output2.= "<td>".$factory_name."</td>";
			    $output2.= "<td>".$factory_address."</td>";
                
                $output2.= "<td>".date('d-m-Y', strtotime($date_time))."</td>";
               
             
                $output2.= "<td>".$desc_incident."</td>";
                $output2.= "<td>".$no_person."</td>";
                $output2.= "<td >".$legal_action."</td>";
				
				$output2.= "<td >".$remarks."</td>";
			
			  	$output2.= "<td >".$del_preper."</td>";
              
			   $output2 .= "</tr>";
	          }
              $output2 .= "</table>";
			  
			

	
	   }
	}
	 $form['step2Cfield']['prpersonlistb'] = array(
	 	'#prefix' => '<div align="left" id="step2_part3_div">'.$output2,
		'#suffix' => '</div>',
       
	);





             //part D

        $form['step2Dfield'] = array(
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 

          $form['step2Dfield']['colD1'] = array
              (
		       '#prefix' => '<div class="table-panel-header"><b>2(D) Number of cases of poisoning and diseases</b> </div>
  			<div class="table-responsive">
		   <table class="table table-striped table-bordered table-responsive admin-custom-table">
		   <thead>
		   <tr><th >', 
		       '#markup'=>'<b> Name of the Factory (R/UR)  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );

            $form['step2Dfield']['colD2'] = array
              (
		       '#prefix' => '<th >', 
		       '#markup'=>'<b> Address of the Factory  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );

               $form['step2Dfield']['colD3'] = array
              (
		       '#prefix' => '<th colspan="10" >', 
		       '#markup'=>'<b> No. of Cases  </b>',

		          '#suffix'=>'</th></tr></thead>',
	   
	   
           );      

           $form['step2Dfield']['colD1val'] = array
              (
		       '#prefix' => '<tr><td rowspan="6" >', 
		        '#type' => 'textarea',
                  '#rows' => 5,
                 '#cols' => 5,
		          '#suffix'=>'</td>',
	   
	   
           );            

         $form['step2Dfield']['colD2val'] = array
              (
		       '#prefix' => '<td rowspan="6" >', 
		        '#type' => 'textarea',
                  '#rows' => 5,
                 '#cols' => 5,
		          '#suffix'=>'</td>',
	   
	   
           );   
         $form['step2Dfield']['colD4'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Lead <br> Poisoning  </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

            $form['step2Dfield']['colD5'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Lead <br> Thetraethyl <br> Poisoning  </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

            $form['step2Dfield']['colD6'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Phosphorous <br> Poisoning  </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

      $form['step2Dfield']['colD7'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Mercury <br> Poisoning  </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

            $form['step2Dfield']['colD8'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Manganese <br> Poisoning  </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

           $form['step2Dfield']['colD9'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Arsenic <br> Poisoning  </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

             $form['step2Dfield']['colD10'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Poisoning <br> by  <br> Nitrous <br> Fumes  </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

            $form['step2Dfield']['colD11'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Carbon <br> Biusulphide <br> Poisoning  </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

            $form['step2Dfield']['colD12'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Benzene <br> Poisoning  </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

            $form['step2Dfield']['colD13'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Chrome <br> Ulceration  </b>',

		          '#suffix'=>'</td></tr>',
	   
	   
           ); 

              $form['step2Dfield']['colD4val'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           ); 

            $form['step2Dfield']['colD5val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           ); 

           $form['step2Dfield']['colD6val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

          
           $form['step2Dfield']['colD7val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

           $form['step2Dfield']['colD8val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

           $form['step2Dfield']['colD9val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

           $form['step2Dfield']['colD10val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

           $form['step2Dfield']['colD11val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

           $form['step2Dfield']['colD12val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

            $form['step2Dfield']['colD13val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td></tr>',
	   
	   
           );



          
               $form['step2Dfield']['colD14'] = array
              (
		       '#prefix' => '<tr><td >', 
		       '#markup'=>'<b> Anthrax  </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

            $form['step2Dfield']['colD15'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Silicosis  </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

            $form['step2Dfield']['colD16'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Poisoning <br> by <br> Halogens<br> or<br> their <br>derivatives  </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

      $form['step2Dfield']['colD17'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Pathological <br>manifestation <br>due to<br> radioactive <br>substances <br>or X-Rays  </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

            $form['step2Dfield']['colD18'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Primary <br>Epitheliomatous <br>cancer <br>of skin  </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

           $form['step2Dfield']['colD19'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Toxic <br> Anemia  </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

             $form['step2Dfield']['colD20'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Toxic <br>Jaundice  </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

            $form['step2Dfield']['colD21'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Oil Cancer <br>of <br> dermatitis  </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

            $form['step2Dfield']['colD22'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Byssinosis  </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

            $form['step2Dfield']['colD23'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Asbestosis  </b>',

		          '#suffix'=>'</td></tr>',
	   
	   
           ); 

              $form['step2Dfield']['colD14val'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           ); 

            $form['step2Dfield']['colD15val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           ); 

           $form['step2Dfield']['colD16val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

           $form['step2Dfield']['colD17val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );
           $form['step2Dfield']['colD18val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

           $form['step2Dfield']['colD19val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

           $form['step2Dfield']['colD20val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

           $form['step2Dfield']['colD21val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

           $form['step2Dfield']['colD22val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

           $form['step2Dfield']['colD23val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td></tr>',
	   
	   
           );


           
              

            $form['step2Dfield']['colD24'] = array
              (
		       '#prefix' => '<tr><td >', 
		       '#markup'=>'<b> Occupational or <br>contact <br> dermatitis  </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

            $form['step2Dfield']['colD25'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Noise <br>induced <br> hearing loss   </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

      $form['step2Dfield']['colD26'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Berylium<br> Poisoning   </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

            $form['step2Dfield']['colD27'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Carbon <br>Monoxide<br> Poisoning   </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

           $form['step2Dfield']['colD28'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Coal miners<br> pneumoconiosis   </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

             $form['step2Dfield']['colD29'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Phosgene<br> Poisoning   </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

            $form['step2Dfield']['colD30'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Occupational <br>Cancer   </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

            $form['step2Dfield']['colD31'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Isocyanates<br> Poisoning   </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

            $form['step2Dfield']['colD32'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Toxic <br>nephritis   </b>',

		          '#suffix'=>'</td>',
	   
	   
           ); 

            $form['step2Dfield']['colD33'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Total  </b>',

		          '#suffix'=>'</td></tr>',
	   
	   
           ); 

              $form['step2Dfield']['colD24val'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           ); 

            $form['step2Dfield']['colD25val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           ); 

           $form['step2Dfield']['colD26val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

           $form['step2Dfield']['colD27val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );
           $form['step2Dfield']['colD28val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

           $form['step2Dfield']['colD29val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

           $form['step2Dfield']['colD30val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

           $form['step2Dfield']['colD31val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

           $form['step2Dfield']['colD32val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

           $form['step2Dfield']['colD33val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td></tr></table></div>',
	   
	   
           );


           

            

          




			$form['step2Dfield']['submit_button']					= array(
																 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
																'#type'					=>'submit',
																'#value'				=>t(' Submit '),
																 '#submit' => array('step2_partd_save'),
																);
		 
		 
	
	 	
       
        $output4='';
      if(trim($filenumber)){
      $query_tab_2_c=db_query('select  *  from labour_factory_statcell_annual_report_t2_d where  annual_inspection_id = :anid', array(':anid' => trim($filenumber) ));
      if($query_tab_2_c->rowCount() > 0) 
              { 
     $output4 = "<div class='table-responsive'>
		   <table class='table table-striped table-bordered table-responsive admin-custom-table add-employee-table-view'>
		   <thead>
       <tr > <th >SL.NO</th>
	     <th >Name of the Factory (R/UR)</th>
      
       <th > Address of the Factory</th>
	    <th >Total</th>
       
		
       
		 
		 <th >DELETE</th>
		</tr></thead>";  
			  $i=0;
		foreach($query_tab_2_c as $squan) {
			$i++;
		      $row_id = $squan->row_id; 
		      $annual_inspection_id = $squan->annual_inspection_id; 
	          $factory_name=$squan->factory_name;
			  $factory_address=$squan->factory_address;
			   $total=$squan->total;
			 
			 
             
              
              
			

			   $bb=$base_root.$base_path.'admin/annual-report-tab2-partd-del/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
		
		      $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
		
		
		
		      $del_preper=l(t('Delete'),$bb ,array('html'=>TRUE)) ;
			  
			  
			  
              if($i%2==0){
		        $output4 .= "<tr>";
				 }
				else
				{
				$output4 .= "<tr >";
				}
				$output4.= "<td>".$i."</td>"; 
				$output4.= "<td>".$factory_name."</td>";
			    $output4.= "<td>".$factory_address."</td>";
                $output4.= "<td>".$total."</td>";
               
			
			  	$output4.= "<td >".$del_preper."</td>";
              
			   $output4 .= "</tr>";
	          }
              $output4 .= "</table></div>";
			  
			

	
	   }
	}
	 $form['step2Dfield']['prpersonlistd'] = array(
	 	'#prefix' => '<div align="left" id="step2_part4_div">'.$output4,
		'#suffix' => '</div>',
       
	);


	
		
		
 
		
				
	
														
														  
	        return $form; 
  }


function step2_partd_save($form , $form_state) {	

                global $base_root, $base_path,$full_base;

 $full_base='';


$val=$form_state['values'];
//print_r($val);
//exit;


    $colD1val=trim($val['colD1val']); 
    $colD2val=trim($val['colD2val']); 

    $inspectionid=trim($val['inspectionid']);
    //part A
	$colD4val=trim($val['colD4val']); if(!$colD4val)     $colD4val= NULL;   
	$colD5val=trim($val['colD5val']); if(!$colD5val)     $colD5val= NULL;   
	$colD6val=trim($val['colD6val']); if(!$colD6val)     $colD6val= NULL;  
	$colD7val=trim($val['colD7val']); if(!$colD7val)     $colD7val= NULL;   
	$colD8val=trim($val['colD8val']); if(!$colD8val)     $colD8val= NULL;   
	$colD9val=trim($val['colD9val']); if(!$colD9val)     $colD9val= NULL; 
	$colD10val=trim($val['colD10val']); if(!$colD10val)  $colD10val= NULL;   
	$colD11val=trim($val['colD11val']); if(!$colD11val)  $colD11val= NULL; 
	$colD12val=trim($val['colD12val']); if(!$colD12val)  $colD12val= NULL;  
	$colD13val=trim($val['colD13val']); if(!$colD13val)  $colD13val= NULL; 


	$colD14val=trim($val['colD14val']); if(!$colD14val)     $colD14val= NULL;   
	$colD15val=trim($val['colD15val']); if(!$colD15val)     $colD15val= NULL;   
	$colD16val=trim($val['colD16val']); if(!$colD16val)     $colD16val= NULL;  
	$colD17val=trim($val['colD17val']); if(!$colD17val)     $colD17val= NULL;   
	$colD18val=trim($val['colD18val']); if(!$colD18val)     $colD18val= NULL;   
	$colD19val=trim($val['colD19val']); if(!$colD19val)     $colD19val= NULL; 
	$colD20val=trim($val['colD20val']); if(!$colD20val)     $colD20val= NULL;   
	$colD21val=trim($val['colD21val']); if(!$colD21val)     $colD21val= NULL; 
	$colD22val=trim($val['colD22val']); if(!$colD22val)     $colD22val= NULL;  
	$colD23val=trim($val['colD23val']); if(!$colD23val)     $colD23val= NULL; 



	$colD24val=trim($val['colD24val']); if(!$colD24val)     $colD24val= NULL;   
	$colD25val=trim($val['colD25val']); if(!$colD25val)     $colD25val= NULL;   
	$colD26val=trim($val['colD26val']); if(!$colD26val)     $colD26val= NULL;  
	$colD27val=trim($val['colD27val']); if(!$colD27val)     $colD27val= NULL;   
	$colD28val=trim($val['colD28val']); if(!$colD28val)     $colD28val= NULL;   
	$colD29val=trim($val['colD29val']); if(!$colD29val)     $colD29val= NULL; 
	$colD30val=trim($val['colD30val']); if(!$colD30val)     $colD30val= NULL;   
	$colD31val=trim($val['colD31val']); if(!$colD31val)     $colD31val= NULL; 
	$colD32val=trim($val['colD32val']); if(!$colD32val)     $colD32val= NULL;  
	$colD33val=trim($val['colD33val']); if(!$colD33val)     $colD33val= NULL; 

	


   

     $txn = db_transaction();
	  try {

               


             
		
	     




	  	 $maxresult=db_query('select  max(row_id) maxsl from labour_factory_statcell_annual_report_t2_d');	
	        $result=$maxresult->fetchAssoc();
	        $max_sl_number = trim($result['maxsl']); 
            if($max_sl_number==0){$querystring=1;	}else{ $querystring=$max_sl_number+1; }
		    $autoGENNO=$querystring;

 $fieldsE = array('row_id' => $autoGENNO, 'annual_inspection_id' =>$inspectionid,'factory_name' =>$colD1val, 'factory_address' => $colD2val, 'lead_poisoning_no' => $colD4val, 'lead_tetraethyl_poisoning_no' => $colD5val, 'phosphorus_poisoning_no' => $colD6val, 'mercury_poisoning_no' => $colD7val, 'manganese_poisoning_no' => $colD8val, 'arsenic_poisoning_no' => $colD9val, 'nitrous_fumes_no' => $colD10val, 'carbon_biusulphide_poisoning_no' => $colD11val, 'benzene_poisoning_no' => $colD12val, 'chrome_ulceration_no' => $colD13val,

    'anthrax' => $colD14val, 'silicosis' => $colD15val, 'halogens_derivatives_poisoning_no' => $colD16val, 'pathological_manifestation_no' => $colD17val, 'epitheliomatous_cancer_no' => $colD18val, 'toxic_anemia_no' => $colD19val, 'toxic_jaundice_no' => $colD20val, 'oil_cancer_no' => $colD21val, 'byssinosis_no' => $colD22val, 'asbestosis_no' => $colD23val ,


     'contact_dermatitis_no' => $colD24val, 'hearing_loss_no' => $colD25val, 'beryllium_poisoning_no' => $colD26val, 'co_poisoning_no' => $colD27val, 'pneumoconiosis_no' => $colD28val, 'phosgene_poisoning_no' => $colD29val, 'occupational_cancer_no' => $colD30val, 'isocyanates_poisoning_no' => $colD31val, 'toxic_nephritis_no' => $colD32val, 'total' => $colD33val 









);
		  
		   
                      db_insert('labour_factory_statcell_annual_report_t2_d')->fields($fieldsE)->execute();

                       $full_base=$base_root.$base_path.'admin/annual-report/step2/'.encryption_decryption_fun('encrypt',$inspectionid);
                   
                         $message = 'DATA  SAVED  SUCCESSFULLY  . ';
                      
				 
	           
	              drupal_set_message(t($message));
				       //$full_base=$base_root.$base_path.'admin/annual-report/'.encryption_decryption_fun('encrypt',$autoGENNO);
				 
	           
	             drupal_goto($full_base);



     }
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/annual-report/step2/'.encryption_decryption_fun('encrypt',$inspectionid);

             $message = 'DATA  NOT SAVED  . ';
                      
		   
                      drupal_set_message(t($message));
	           
	             drupal_goto($full_base);
	
     }	

 }




function step2_parta_save($form , $form_state) {	

                global $base_root, $base_path,$full_base;

 $full_base='';


$val=$form_state['values'];
//print_r($val);
//exit;


    $inspectionid=trim($val['inspectionid']);
    //part A
	$colA3val=trim($val['colA3val']); if(!$colA3val)  $colA3val= NULL;   
	$colA4val=trim($val['colA4val']); if(!$colA4val)  $colA4val= NULL;   
	$colA5val=trim($val['colA5val']); if(!$colA5val)  $colA5val= NULL;   

	$colA6val=trim($val['colA6val']); if(!$colA6val)  $colA6val= NULL;   
    $colA7val=trim($val['colA7val']); if(!$colA7val)  $colA7val= NULL;   
    $colA8val=trim($val['colA8val']); if(!$colA8val)  $colA8val= NULL;   
    $colA9val=trim($val['colA9val']); if(!$colA9val)  $colA9val= NULL;   
    $colA10val=trim($val['colA10val']); if(!$colA10val) $colA10val= NULL; 



    $colA13val=trim($val['colA13val']); if(!$colA13val)  $colA13val= NULL;   
	$colA14val=trim($val['colA14val']); if(!$colA14val)  $colA14val= NULL;   
	$colA15val=trim($val['colA15val']); if(!$colA15val)  $colA15val= NULL;   

	$colA16val=trim($val['colA16val']); if(!$colA16val)  $colA16val= NULL;   
    $colA17val=trim($val['colA17val']); if(!$colA17val)  $colA17val= NULL;   
    $colA18val=trim($val['colA18val']); if(!$colA18val)  $colA18val= NULL;   
    $colA19val=trim($val['colA19val']); if(!$colA19val)  $colA19val= NULL;   
    $colA20val=trim($val['colA20val']); if(!$colA20val)  $colA20val= NULL; 




     $txn = db_transaction();
	  try {

                  $query_update_a_yes=db_query('select  * from labour_factory_statcell_annual_report_t2_a where  annual_inspection_id = :filenumber', array(':filenumber' => $inspectionid));


             
		
	     if($query_update_a_yes->rowCount() > 0 ) {
       
         $query_update_B = db_update('labour_factory_statcell_annual_report_t2_a');
      $query_update_B->fields(array(
		    'ado_no_of_accidents_fatal' =>$colA3val, 'ado_no_of_accidents_serious' => $colA4val, 'ado_no_danger_occur_explosion' => $colA5val, 'ado_no_danger_occur_fire' => $colA6val, 'ado_no_danger_occur_gassing' => $colA7val, 'ado_no_danger_occur_toxic_release' => $colA8val, 'ado_no_danger_occur_collapse' => $colA9val, 'ado_no_danger_occur_others' => $colA10val, 'ado_no_visit_paid_fatal_accidents' => $colA13val, 'ado_no_visit_paid_serious_accidents' => $colA14val, 'ado_no_visit_paid_explosion' => $colA15val, 'ado_no_visit_paid_fire' => $colA16val, 'ado_no_visit_paid_gassing' => $colA17val,'ado_no_visit_paid_toxic_release' => $colA18val,'ado_no_visit_paid_collapse' => $colA19val,'ado_no_visit_paid_others' => $colA20val ));
										
										
										
       $query_update_B->condition('annual_inspection_id',$inspectionid);
       $query_update_B->execute(); 
        $full_base=$base_root.$base_path.'admin/annual-report/step2/'.encryption_decryption_fun('encrypt',$inspectionid);

	      }
	      else
	      {




	  	 $maxresult=db_query('select  max(row_id) maxsl from labour_factory_statcell_annual_report_t2_a');	
	        $result=$maxresult->fetchAssoc();
	        $max_sl_number = trim($result['maxsl']); 
            if($max_sl_number==0){$querystring=1;	}else{ $querystring=$max_sl_number+1; }
		    $autoGENNO=$querystring;

 $fieldsE = array('row_id' => $autoGENNO, 'annual_inspection_id' =>$inspectionid,'ado_no_of_accidents_fatal' =>$colA3val, 'ado_no_of_accidents_serious' => $colA4val, 'ado_no_danger_occur_explosion' => $colA5val, 'ado_no_danger_occur_fire' => $colA6val, 'ado_no_danger_occur_gassing' => $colA7val, 'ado_no_danger_occur_toxic_release' => $colA8val, 'ado_no_danger_occur_collapse' => $colA9val, 'ado_no_danger_occur_others' => $colA10val, 'ado_no_visit_paid_fatal_accidents' => $colA13val, 'ado_no_visit_paid_serious_accidents' => $colA14val, 'ado_no_visit_paid_explosion' => $colA15val, 'ado_no_visit_paid_fire' => $colA16val, 'ado_no_visit_paid_gassing' => $colA17val,'ado_no_visit_paid_toxic_release' => $colA18val,'ado_no_visit_paid_collapse' => $colA19val,'ado_no_visit_paid_others' => $colA20val);
		  
		   
                      db_insert('labour_factory_statcell_annual_report_t2_a')->fields($fieldsE)->execute();

                       $full_base=$base_root.$base_path.'admin/annual-report/step2/'.encryption_decryption_fun('encrypt',$inspectionid);
                    }
                         $message = 'DATA  SAVED  SUCCESSFULLY  . ';
                      
				 
	           
	              drupal_set_message(t($message));
				       //$full_base=$base_root.$base_path.'admin/annual-report/'.encryption_decryption_fun('encrypt',$autoGENNO);
				 
	           
	             drupal_goto($full_base);



     }
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/annual-report/step2/'.encryption_decryption_fun('encrypt',$inspectionid);

             $message = 'DATA  NOT SAVED  . ';
                      
		   
                   drupal_set_message(t($message));
	           
	             drupal_goto($full_base);
	
     }	

 }


function an_classification_option() {
	$blk="SELECT * FROM {labour_factory_accident_classification_mst} ORDER BY classification_class";
	
    $state_query=db_query($blk);

  $options 				= array();
	
	foreach($state_query as $state_result) {
		
		$options[$state_result->accident_classification_id] =$state_result->classification_class.'-'.$state_result->classification_details;	 
	
	}
	
	
	
   
       return $options;
		
  
      
	
	
}

function add_step2_partb_data($form , $form_state) {	
       global $base_root, $base_path;
       $val=$form_state['values'];


    
 
      $inspectionid=trim($val['inspectionid']);
      $colB1val=trim($val['colB1val']); 
      $colB2val=trim($val['colB2val']);   //if(!$colB2val)   $colB2val= NULL;  
      $colB3val=trim($val['colB3val']);  
      $colB4val=trim($val['colB4val']);  
      $colB5val=trim($val['colB5val']);   
      $colB6val=trim($val['colB6val']);  
      $colB7val=trim($val['colB7val']);  
      $colB8val=trim($val['colB8val']);   
      $colB9val=trim($val['colB9val']); 
      $colB10val=trim($val['colB10val']);       


   if(!$colB1val)
	 {
	  drupal_get_messages(error);
	  return "<font color='#FF3333'><b>please select accident type <b>    </font>";
	  exit;
	 } 

	 
	    


     $txn = db_transaction();

        try {
     
	 
	  $ins_pr_person=db_query('select  max(row_id) ownermax from labour_factory_statcell_annual_report_t2_b ');
	foreach($ins_pr_person as $energy) {
	
	    $ownermax = $energy->ownermax; 
        
		
	}
		
	 if($ins_pr_person->rowCount()==0) 
        { 
		$count_profile=1;
		}
		else
		{
		$count_profile=$ownermax+1;	
			
		}
			
	      
	  $colB1val=trim($val['colB1val']); 
      $colB2val=trim($val['colB2val']);   //if(!$colB2val)   $colB2val= NULL;  
      $colB3val=trim($val['colB3val']);  
      $colB4val=trim($val['colB4val']);  
      $colB5val= date('Y-m-d', strtotime(trim($val['colB5val'])))  ;
      $colB6val= date('Y-m-d', strtotime(trim($val['colB6val']))) ;
      $colB7val=trim($val['colB7val']);  
      $colB8val=trim($val['colB8val']);   
      $colB9val=trim($val['colB9val']); 
		   
		    $fieldsE = array('row_id' => $count_profile, 'annual_inspection_id' => $inspectionid,'accident_type' =>$colB1val ,'acc_det_name_of_factory' =>$colB2val,'acc_det_address_of_factory' =>$colB3val, 'acc_det_name_of_deceased_injured' => $colB4val, 'acc_det_date_of_accident' => $colB5val, 'acc_det_expiry' => $colB6val, 'acc_det_section_violation' => $colB7val , 'classification_code' => $colB8val , 'acc_det_action_case_no' => $colB9val , 'remarks' => $colB10val);
		  
		   
           db_insert('labour_factory_statcell_annual_report_t2_b')->fields($fieldsE)->execute();	
	 
	 
	//$query_tab_1_c=db_query('select  *  from labour_factory_statcell_annual_report_t2_b where  annual_inspection_id = :anid', array(':anid' => trim($inspectionid) ));

$query_tab_1_c=db_query('select  *  from labour_factory_statcell_annual_report_t2_b a, labour_factory_accident_classification_mst b where  CAST (a.classification_code AS INTEGER)=b.accident_classification_id and annual_inspection_id = :anid', array(':anid' => trim($inspectionid) ));



    
      $output1 = "
     <div class='table-responsive'>
      <table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
	    <tr > <th >Fatal / Serious</th>
      
       <th > Name Of Factory(R/UR)</th>
	    <th >Address of the factories(R/UR)</th>
       
		 <th >Name of injured/deceased persons</th>

		 <th >Date of Occurrence</th>
       
		 <th >Date of Expiry</th>
		  <th >Infringement Section/Rule Violated</th>
       
		 <th >Classification</th>
		  <th >Legal Action Taken(Case No.)</th>
		   <th >Remarks</th>
		 <th >DELETE</th>
		</tr>";  
			  $i=0;
		foreach($query_tab_1_c as $squan) {
			$i++;
		      $row_id = $squan->row_id; 
		      $annual_inspection_id = $squan->annual_inspection_id; 
	          $accident_type=$squan->accident_type;
			  $acc_det_name_of_factory=$squan->acc_det_name_of_factory;
			  $acc_det_address_of_factory=$squan->acc_det_address_of_factory;
              $acc_det_name_of_deceased_injured=$squan->acc_det_name_of_deceased_injured;

              //$acc_det_date_of_accident=$val['acc_det_date_of_accident']['year'].'-'.$val['acc_det_date_of_accident']['month'].'-'.$val['acc_det_date_of_accident']['day'];

            //$acc_det_expiry=$val['acc_det_expiry']['year'].'-'.$val['acc_det_expiry']['month'].'-'.$val['acc_det_expiry']['day'];
             $acc_det_section_violation=$squan->acc_det_section_violation;
              $classification_code=$squan->classification_code;
              $acc_det_action_case_no=$squan->acc_det_action_case_no;
              $remarks=$squan->remarks;

             $acc_det_expiry= !empty(trim($squan->acc_det_expiry)) ? date('d-m-Y', strtotime($squan->acc_det_expiry)) : ' ';
              
              
			

			   $bb=$base_root.$base_path.'admin/annual-report-tab2-partb-del/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
		
		      $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
		
		
		
		      $del_preper=l(t('Delete'),$bb ,array('html'=>TRUE)) ;
			  
			  
			  
              if($i%2==0){
		        $output1 .= "<tr>";
				 }
				else
				{
				$output1 .= "<tr>";
				}
				//$output1.= "<td>".$i."</td>"; 
				$output1.= "<td>".$accident_type."</td>";
			    $output1.= "<td>".$acc_det_name_of_factory."</td>";
                $output1.= "<td>".$acc_det_address_of_factory."</td>";
                $output1.= "<td>".$acc_det_name_of_deceased_injured."</td>";
                $output1.= "<td>".date('d-m-Y', strtotime($squan->acc_det_date_of_accident))."</td>";
                $output1.= "<td>".$acc_det_expiry."</td>";
             
                $output1.= "<td>".$acc_det_section_violation."</td>";
                $output1.= "<td>".$squan->classification_details."</td>";
                $output1.= "<td >".$acc_det_action_case_no."</td>";
				
				$output1.= "<td >".$remarks."</td>";
				$output1.= "<td >".$del_preper."</td>";
			
              
			   $output1 .= "</tr>";
	          }
              $output1 .= "</table></div>";
			  
			

	
	   



	  }
  catch (Exception $e) {
    $form_state['rebuild'] = TRUE;
 
    $txn->rollback();
  
    watchdog_exception('type', $e);
	$output1 = ' DATA NOT INSERT';
  }  
	


                          drupal_get_messages(error);
		                  return $output1;
		                  exit;
                          
                          }


  function step2_part2_row_del(  $filenumber = NULL , $rowid = NULL){
	  
	 global $base_root, $base_path;
	 

	   $filenumber=  encryption_decryption_fun('decrypt',trim($filenumber));
	   
      $rowid=  encryption_decryption_fun('decrypt',trim($rowid));
	   
	$txn = db_transaction();
	  try {
		  
    db_delete('labour_factory_statcell_annual_report_t2_b')
    ->condition('annual_inspection_id',trim($filenumber))
	->condition('row_id',trim($rowid))
    ->execute();
	
	
	$message = '   delete is successfull ';
	
}
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);
	$message = '    row is not  delete ';
     }	
	
     //$aa=$base_root.$base_path.'equalremuins/equalinfringements/'.encryption_decryption_fun('encrypt', trim($filenumber));

      $aa=$base_root.$base_path.'admin/annual-report/step2/'.encryption_decryption_fun('encrypt',$filenumber);
     drupal_set_message(t($message));
		 
		  drupal_goto($aa);
		  
  }





  function add_step2_partc_data($form , $form_state) {	
       global $base_root, $base_path;
       $val=$form_state['values'];


    
 
      $inspectionid=trim($val['inspectionid']);
      $colC1val=trim($val['colC1val']); 
      $colC2val=trim($val['colC2val']);   //if(!$colB2val)   $colB2val= NULL;  
      $colC3val=   date('Y-m-d', strtotime(trim($val['colC3val']))) ;
      $colC4val=trim($val['colC4val']);  
      $colC5val=trim($val['colC5val']);   if(!$colC5val)   $colC5val= NULL;  
      $colC6val=trim($val['colC6val']);  
      $colC7val=trim($val['colC7val']);  
        


   if(!preg_match('/^[0-9]+$/',trim($colC5val)))
	 {
	  drupal_get_messages(error);
	  return "<font color='#FF3333'><b>please give integer value the  no. of persons involved   <b>    </font>";
	  exit;
	 }


	 
	    


     $txn = db_transaction();

        try {
     
	 
	  $ins_pr_person=db_query('select  max(row_id) ownermax from labour_factory_statcell_annual_report_t2_c ', array(':filenumber' => $inspectionid));
	foreach($ins_pr_person as $energy) {
	
	    $ownermax = $energy->ownermax; 
        
		
	}
		
	 if($ins_pr_person->rowCount()==0) 
        { 
		$count_profile=1;
		}
		else
		{
		$count_profile=$ownermax+1;	
			
		}
			
	      
	 
		   
		    $fieldsE = array('row_id' => $count_profile, 'annual_inspection_id' => $inspectionid,'factory_name' =>$colC1val ,'factory_address' =>$colC2val,'date_time' =>$colC3val, 'desc_incident' => $colC4val, 'no_person' => $colC5val, 'legal_action' => $colC6val, 'remarks' => $colC7val );
		  
		   
           db_insert('labour_factory_statcell_annual_report_t2_c')->fields($fieldsE)->execute();	
	 
	 
	$query_tab_1_c=db_query('select  *  from labour_factory_statcell_annual_report_t2_c where  annual_inspection_id = :anid', array(':anid' => trim($inspectionid) ));
    
       $output2 = "<div class='table-responsive'><table class='table table-striped table-bordered table-responsive admin-custom-table'>
	   <thead>
	    <tr > <th >Name of the Factory (R/UR)</th>
      
       <th > Address of the Factory</th>
	    <th >Date and hour of occurrence</th>
       
		 <th >Description of the incident</th>

		 <th >No. of persons involved</th>
       
		 <th >Legal Action taken (with case no.)</th>
		  <th >Remarks</th>
       
		 
		 <th >DELETE</th>
		</tr></thead>";  
			  $i=0;
		foreach($query_tab_1_c as $squan) {
			$i++;
		      $row_id = $squan->row_id; 
		      $annual_inspection_id = $squan->annual_inspection_id; 
	          $factory_name=$squan->factory_name;
			  $factory_address=$squan->factory_address;
			  $date_time=$squan->date_time;
              $desc_incident=$squan->desc_incident;

              //$acc_det_date_of_accident=$val['acc_det_date_of_accident']['year'].'-'.$val['acc_det_date_of_accident']['month'].'-'.$val['acc_det_date_of_accident']['day'];

            //$acc_det_expiry=$val['acc_det_expiry']['year'].'-'.$val['acc_det_expiry']['month'].'-'.$val['acc_det_expiry']['day'];
             $no_person=$squan->no_person;
              $legal_action=$squan->legal_action;
              $remarks=$squan->remarks;
             
              
              
			

			   $bb=$base_root.$base_path.'admin/annual-report-tab2-partc-del/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
		
		      $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
		
		
		
		      $del_preper=l(t('Delete'),$bb ,array('html'=>TRUE)) ;
			  
			  
			  
              if($i%2==0){
		        $output2 .= "<tr>";
				 }
				else
				{
				$output2 .= "<tr>";
				}
				//$output1.= "<td>".$i."</td>"; 
				$output2.= "<td>".$factory_name."</td>";
			    $output2.= "<td>".$factory_address."</td>";
                
                $output2.= "<td>".date('d-m-Y', strtotime($date_time))."</td>";
               
             
                $output2.= "<td>".$desc_incident."</td>";
                $output2.= "<td>".$no_person."</td>";
                $output2.= "<td >".$legal_action."</td>";
				
				$output2.= "<td >".$remarks."</td>";
				$output2.= "<td >".$del_preper."</td>";
			
			
              
			   $output2 .= "</tr>";
	          }
              $output2 .= "</table></div>";
			  
			

	
	   



	  }
  catch (Exception $e) {
    $form_state['rebuild'] = TRUE;
 
    $txn->rollback();
  
    watchdog_exception('type', $e);
	$output2 = ' DATA NOT INSERT';
  }  
	


                          drupal_get_messages(error);
		                  return $output2;
		                  exit;
                          
                          }


  function step2_part2_row3_del(  $filenumber = NULL , $rowid = NULL){
	  
	 global $base_root, $base_path;
	  //  $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));
	   
      //$tyinfg= encryption_decryption_fun('decrypt', trim($tyinfg));

	   $filenumber=  encryption_decryption_fun('decrypt',trim($filenumber));
	   
      $rowid=  encryption_decryption_fun('decrypt',trim($rowid));
	   
	$txn = db_transaction();
	  try {
		  
    db_delete('labour_factory_statcell_annual_report_t2_c')
    ->condition('annual_inspection_id',trim($filenumber))
	->condition('row_id',trim($rowid))
    ->execute();
	
	
	$message = '   delete is successfull ';
	
}
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);
	$message = '    row is not  delete ';
     }	
	
     //$aa=$base_root.$base_path.'equalremuins/equalinfringements/'.encryption_decryption_fun('encrypt', trim($filenumber));

      $aa=$base_root.$base_path.'admin/annual-report/step2/'.encryption_decryption_fun('encrypt',$filenumber);
     drupal_set_message(t($message));
		 
		  drupal_goto($aa);
		  
  }

  function step2_partd_row_del(  $filenumber = NULL , $rowid = NULL){
	  
	 global $base_root, $base_path;
	  //  $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));
	   
      //$tyinfg= encryption_decryption_fun('decrypt', trim($tyinfg));

	   $filenumber=  encryption_decryption_fun('decrypt',trim($filenumber));
	   
      $rowid=  encryption_decryption_fun('decrypt',trim($rowid));
     // print $filenumber.'ddd'. $rowid;
     // exit;
	   
	$txn = db_transaction();
	  try {
		  
    db_delete('labour_factory_statcell_annual_report_t2_d')
    ->condition('annual_inspection_id',trim($filenumber))
	->condition('row_id',trim($rowid))
    ->execute();
	
	
	$message = '   delete is successfull ';
	
}
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);
	$message = '    row is not  delete ';
     }	
	
     //$aa=$base_root.$base_path.'equalremuins/equalinfringements/'.encryption_decryption_fun('encrypt', trim($filenumber));

      $aa=$base_root.$base_path.'admin/annual-report/step2/'.encryption_decryption_fun('encrypt',$filenumber);
     drupal_set_message(t($message));
		 
		  drupal_goto($aa);
		  
  }
