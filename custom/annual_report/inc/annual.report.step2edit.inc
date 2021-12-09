<?php

function anr_step2_part2_edit($ajax, $filenumber = NULL , $rowid = NULL){
	
	 if ($ajax) {
     // Required includes for ctools to work:
    
 
    ctools_include('ajax');
    ctools_include('modal');
	  ctools_modal_add_js();
     $form_state = array(
       'ajax' => TRUE,
       'title' => t('Edit  Details of Accidents(Fatal/Serious)'),
	   
     );
	  //$id=9;
	  $form_state['build_info']['args'] = array($filenumber , $rowid);
	 // $form_state['build_info']['args'] = array($rowid);
      $output = ctools_modal_form_wrapper('anr_part2_partb_edit_frm', $form_state);
	  
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }

   
    
	print ajax_render($output);
    drupal_exit();
     
   } else {
     return drupal_get_form('anr_part2_partb_edit_frm');
   }
   }


   function anr_part2_partb_edit_frm( $form, &$form_state   ){
   // drupal_add_css(drupal_get_path('module', 'applicant_forms') . '/css/clra_applications.css');  
     
      global $base_root, $base_path, $user;

          $uid  = $user->uid;
     
       
       
       $filenumber =  encryption_decryption_fun('decrypt',$form_state['build_info']['args'][0]);      
       
       
        $rowid =  encryption_decryption_fun('decrypt',$form_state['build_info']['args'][1]);      
       
     
     //print $district_id.'/'.$dic_subdic_tag.'/'.$go_num;
    $form['part2partbedit'] = array(
          '#title' => t(''),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 
      
        
    $form['part2partbedit']['inspectionid'] = 
      array('#type' => 'hidden',  
      '#value' => $filenumber,
     
     );
       $form['part2partbedit']['rowid'] = 
      array('#type' => 'hidden',  
      '#value' => $rowid,
     
     );
      
    
  
   module_load_include('inc', 'annual_report', 'inc/annual.report.step2');
  
 
                       
                         $accident_type=NULL;
                         $acc_det_name_of_factory=NULL;
                         $acc_det_address_of_factory=NULL;
                         $acc_det_name_of_deceased_injured=NULL;
                         $acc_det_section_violation=NULL;
                         $acc_det_action_case_no=NULL;
                         $classification_code=NULL;
                         $remarks=NULL;
                         $acc_det_date_of_accident=NULL;
                        $acc_det_expiry=NULL;
                    
                        
                         if( $filenumber &&   $rowid) 
                         { 


                     

                         $t9_row_query = db_select('labour_factory_statcell_annual_report_t2_b', 'a');
                         $t9_row_query->innerjoin('labour_factory_accident_classification_mst', 'b', '  CAST (a.classification_code AS INTEGER) = b.accident_classification_id');
                         $t9_row_query->condition('a.annual_inspection_id',trim($filenumber),'=');
                         $t9_row_query->condition('a.row_id',trim($rowid),'=');
                         
                       

                          $t9_row_query->fields('a',array('accident_type','acc_det_name_of_factory','acc_det_address_of_factory',
        'acc_det_name_of_deceased_injured','acc_det_section_violation','acc_det_action_case_no','classification_code','remarks','acc_det_date_of_accident','acc_det_expiry'));

                   $t9_row_query_result = $t9_row_query->execute();

                     
                       if( $t9_row_query_result->rowCount() > 0 ) 
                       { 

                      
                         $anr_t9_fetch=$t9_row_query_result->fetchAssoc();

                         $accident_type=$anr_t9_fetch['accident_type'];
                         $acc_det_name_of_factory=$anr_t9_fetch['acc_det_name_of_factory'];
                         $acc_det_address_of_factory=$anr_t9_fetch['acc_det_address_of_factory'];
                         $acc_det_name_of_deceased_injured=$anr_t9_fetch['acc_det_name_of_deceased_injured'];
                         $acc_det_section_violation=$anr_t9_fetch['acc_det_section_violation'];
                         $acc_det_action_case_no=$anr_t9_fetch['acc_det_action_case_no'];
                         $classification_code=$anr_t9_fetch['classification_code'];
                         $remarks=$anr_t9_fetch['remarks'];
                         $acc_det_date_of_accident=date('d-m-Y', strtotime($anr_t9_fetch['acc_det_date_of_accident']));
                        $acc_det_expiry=$anr_t9_fetch['acc_det_expiry'];
                     

                       }
                   }
 


   $form['part2partbedit']['colB1val'] = array(

         '#prefix' => '<div class="form-group "><div class="col-sm-8 col-form-label">', 
   
        '#suffix'=>'</div>',
      
         '#type' => 'radios',
         '#title' => t('Fatal / Serious   '),
      //  '#required' => TRUE,
         '#options' => array(
         'Fatal' => t('Fatal'),
         'Serious' => t('Serious'),
      //'Other' => t('Other'),
         ),
     '#default_value' =>$accident_type,
    
     
         );




           $form['part2partbedit']['colB2val'] = array
              (
                '#title' => t('Name Of Factory(R/UR)   '),  
              '#type' => 'textarea',
           
                '#rows' => 2,
                 '#cols' => 2,

          '#prefix' => '<div class="col-sm-7">', 
   
        '#suffix'=>'</div>',
         '#attributes'    => array('class'=>array('form-control col-form-label my-1')),
           '#default_value' =>$acc_det_name_of_factory,
     
     
           ); 

           $form['part2partbedit']['colB3val'] = array
              (
          
           '#type' => 'textarea',
           
                '#rows' => 2,
                 '#cols' => 2,

         '#prefix' => '<div class="col-sm-7">', 
   
        '#suffix'=>'</div>',
         '#title' => t('Address of the factories(R/UR)   '),
      '#attributes'    => array('class'=>array('form-control my-1')),
        '#default_value' =>$acc_det_address_of_factory,
     
           ); 

           $form['part2partbedit']['colB4val'] = array
              (
          
             '#type' => 'textarea',
           
                '#rows' => 2,
                 '#cols' => 2,

          '#prefix' => '<div class="col-sm-7">', 
   
        '#suffix'=>'</div>',

         '#title' => t('Name of injured/deceased persons   '),
          '#default_value' =>$acc_det_name_of_deceased_injured,
     
     
           ); 

           $form['part2partbedit']['colB5val'] = array
              (
          
          '#title' => t('Date of Occurrence   '),

              '#type' => 'textfield',
    
      // '#attributes'    => array('class'=>array('form-control  datepicker_retify'), 'id'=>'per_workers_service_since_work_id_1'),
      '#attributes' => array('class' => array('datepicker_retify form-control')),

          
          // '#size' => 10,
           '#prefix' => '<div class="col-sm-6">', 
   
        '#suffix'=>'</div>',
         '#default_value' =>$acc_det_date_of_accident,
     
     
     
           ); 

           $form['part2partbedit']['colB6val'] = array
              (
             '#title' => t('Date of Expiry   '),
           
      '#type' => 'textfield',
     // '#attributes'     => array('class'=>array('form-control  datepicker_retify'), 'id'=>'per_workers_service_since_work_id_2'),
      '#attributes' => array('class' => array('datepicker_retify')),

        
         // '#size' => 10,
          '#prefix' => '<div class="col-sm-6">', 
   
        '#suffix'=>'</div>',
          '#default_value' =>$acc_det_expiry,
     
     
           ); 

           $form['part2partbedit']['colB7val'] = array
              (
         '#title' => t('Infringement Section/Rule Violated   '),
           '#type' => 'textarea',
           
                '#rows' => 2,
                 '#cols' => 2,

         '#prefix' => '<div class="col-sm-7">', 
   
        '#suffix'=>'</div>',
     
      '#default_value' =>$acc_det_section_violation,
           ); 

            

           

        $default_vilg='0';
      $options_classification = array(0 => " Select  ") + an_classification_option();

          $form['part2partbedit']['colB8val'] = array(

              '#title' => t('Classification   '),
      
    // '#attributes' => array('class' => array('select-estab-shop')),
        '#type' => 'select',
      //  '#title' => ' GP / Ward',
    //'#element_validate' => array('inspection_district_validate'),
        '#options' => $options_classification,
       // '#default_value' => isset($form_state['values']['inspection_dropdown_forth']) ? $form_state['values']['inspection_dropdown_forth'] : $worker_vill_word ,
     '#default_value' =>  $classification_code ,
     '#prefix' => '<div class="col-sm-8">', 
   
        '#suffix'=>'</div>',
    
    
    ); 


 $form['part2partbedit']['colB9val'] = array
              (
          
           '#type' => 'textarea',
           
                '#rows' => 2,
                 '#cols' => 2,

          '#prefix' => '<div class="col-sm-8">', 
   
        '#suffix'=>'</div>',
           '#title' => t('Legal Action Taken(Case No.)  '),
            '#default_value' =>  $acc_det_action_case_no ,
     
     
           );





            $form['part2partbedit']['colB10val'] = array
              (
         
             '#type' => 'textarea',
           
                '#rows' => 2,
                 '#cols' => 2,

         '#prefix' => '<div class="col-sm-7">', 
   
        '#suffix'=>'</div>',
          '#title' => t('Remarks '),
             '#default_value' =>  $remarks ,
     
     
           ); 

        $form['submit']  = array(
                                 
                                '#prefix' => '<div style="text-align:center;" class="col-sm-12" >',
                                '#suffix'=>'</div><div> &nbsp; </div> </div>', 
                                '#type'         =>'submit',
                                  '#value'        =>t(' Update  '),

                                
                                //'#element_validate' => array('annual_report_validate'),
                                );      
   

    return $form;

} 

function annual_report_step9_submit($form , $form_state) {  

                global $base_root, $base_path,$full_base;

 


$val=$form_state['values'];
 $inspectionid=trim($val['inspectionid']);
 $rowid=trim($val['rowid']);

 $full_base=$base_root.$base_path.'admin/annual-report/step2/'.encryption_decryption_fun('encrypt',$inspectionid);

             $message = 'DATA  NOT SAVED  . ';
                      
       
                      drupal_set_message(t($message));
             
               drupal_goto($full_base);
               }