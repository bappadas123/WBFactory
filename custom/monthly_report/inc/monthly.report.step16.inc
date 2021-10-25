<?php
function month_report_step16( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;

     $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));

     $get_info_montly_report=get_monthly_area_from_to_date($filenumber);

    $form['step16field'] = array(
          '#title' => t('<font color="DarkGreen">'.$get_info_montly_report.'<b>  Information regarding compliance in the factories inspected for  </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          );

     $form['step16field']['monthlyformid'] = 
      array('#type' => 'hidden',  
      '#value' => $filenumber,
     
     );
       $step16_select_query = db_select('labour_factory_statcell_form_5_compliance_for_chemical', 'a');
       
      $step16_select_query->condition('a.monthly_form_id',trim($filenumber),'=');
      
    
        $step16_select_query->fields('a',array( 'on_site_plan_submitted'  ,'safety_audit_conducted' ,'on_site_emergency_mock_drills','no_of_mah_factories_identified' ));
        $step16_select_query_result = $step16_select_query->execute(); 
    
    $result_step16=$step16_select_query_result->fetchAssoc();

     $form['step16field']['one'] = array
              (
           '#prefix' => '<table class="table" border="1"><tr><td  >', 
           '#markup'=>'<b> On site plan submitted/resubmitted for examination  </b>',

              '#suffix'=>'</td>',
     
     
           ); 


            $form['step16field']['two'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b>Safety audit conducted  </b>',

              '#suffix'=>'</td>',
     
     
           ); 
            $form['step16field']['three'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b>On-site emergency mock drills conducted   </b>',

              '#suffix'=>'</td></tr>',
     
     
           ); 

        
           

           $form['step16field']['oneValue'] = array
              (
           '#prefix' => '<td   >', 
           '#type' => 'textfield',
           
           '#suffix'=>'</td>',

            '#default_value' =>$result_step16['on_site_plan_submitted']  

         
     
     
           );

        $form['step16field']['twoValue'] = array
              (
           '#prefix' => '<td   >', 
           '#type' => 'textfield',
           
           '#suffix'=>'</td>',

         '#default_value' =>$result_step16['safety_audit_conducted']  

         
     
     
           );

               $form['step16field']['threeValue'] = array
              (
           '#prefix' => '<td   >', 
           '#type' => 'textfield',
           
           '#suffix'=>'</td></tr>',

           '#default_value' =>$result_step16['on_site_emergency_mock_drills']  

         
     
     
           );
     $form['step16field']['fivehead'] = array
              (
           '#prefix' => '<tr><td colspan="2"  >', 
          '#markup'=>'<b>No of MAH Factories identified  </b>',
           
           '#suffix'=>'</td>',

        
           );

                $form['step16field']['no_of_mah'] = array
              (
           '#prefix' => '<td   >', 
           '#type' => 'textfield',
           
           '#suffix'=>'</td></tr></table>',

          '#default_value' =>$result_step16['no_of_mah_factories_identified']  

         
     
     
           );

                

              
             
             
     $form['step16field']['submit_button']                    = array(
                                                                 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
                                                                '#type'                 =>'submit',
                                                                '#value'                =>t(' Save ')
                                                                );

      return $form;

    }

function month_report_step16_submit($form, &$form_state) {
   global $base_root, $base_path,$full_base;

      $full_base='';


      $val=$form_state['values'];
       //print_r($val);
       //exit;


    $monthlyformid=trim($val['monthlyformid']);

       $oneValue=trim($val['oneValue']);
       $twoValue=trim($val['twoValue']);
       $threeValue=trim($val['threeValue']);

       $no_of_mah=trim($val['no_of_mah']);
      

    $txn = db_transaction();
      try {
          
   
       $query_update_a_yes=db_query('select  * from labour_factory_statcell_form_5_compliance_for_chemical where  monthly_form_id = :filenumber', array(':filenumber' => $monthlyformid));


             
       if($query_update_a_yes->rowCount() > 0) 
          {

      $query_update_B = db_update('labour_factory_statcell_form_5_compliance_for_chemical');
      $query_update_B->fields(array(
             'on_site_plan_submitted' =>$oneValue ,'safety_audit_conducted' => $twoValue ,'on_site_emergency_mock_drills' =>$threeValue ,'no_of_mah_factories_identified' => $no_of_mah ));
                                        
                                        
                                        
       $query_update_B->condition('monthly_form_id',$monthlyformid);
       $query_update_B->execute(); 

         }
         else
         {

          

 $fieldsA = array('monthly_form_id' => $monthlyformid,  'on_site_plan_submitted' => $oneValue  ,'safety_audit_conducted' =>$twoValue ,'on_site_emergency_mock_drills' => $threeValue ,'no_of_mah_factories_identified' =>$no_of_mah  );


   db_insert('labour_factory_statcell_form_5_compliance_for_chemical')->fields($fieldsA)->execute(); 


   

         }



    
    
       $message = '   data save successfully ';
     drupal_set_message(t($message));
     $full_base=$base_root.$base_path.'admin/monthly-report/step16/'.encryption_decryption_fun('encrypt',$monthlyformid);
               
    drupal_goto($full_base);
    
     }
    catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);
    $message = '    data is not save  ';
     drupal_set_message(t($message));

      $full_base=$base_root.$base_path.'admin/monthly-report/step16/'.encryption_decryption_fun('encrypt',$monthlyformid);
               
    drupal_goto($full_base);
     }


}    