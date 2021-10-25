<?php
function month_report_step15( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;

    $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));

     //$options_classification = array(0 => " Select  ") + an_classification_option();

    $form['step15field'] = array(
          '#title' => t('<font color="DarkGreen"><b>  Details of Medical Examination  </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          );

     $form['step15field']['monthlyformid'] = 
      array('#type' => 'hidden',  
      '#value' => $filenumber,
     
     );
       $step15_select_query = db_select('labour_factory_statcell_form_5_medical_examination', 'a');
       
      $step15_select_query->condition('a.monthly_form_id',trim($filenumber),'=');
      
    
        $step15_select_query->fields('a',array( 'adolescent_no_certified'  ,'adolescent_no_recertified' ,'adolescent_no_rejected','children_no_certified' ,'children_no_recertified'  ,'children_no_rejected'  ,'nature_of_industry'  ,'no_of_workers_examined' ,'comments_on_fitness'));
        $step15_select_query_result = $step15_select_query->execute(); 
    
    $result_step15=$step15_select_query_result->fetchAssoc();

     $form['step15field']['one'] = array
              (
           '#prefix' => '<table class="table" border="1"><tr><td rowspan="2" >', 
           '#markup'=>'<b> Young Person  </b>',

              '#suffix'=>'</td>',
     
     
           ); 


            $form['step15field']['two'] = array
              (
           '#prefix' => '<td  style="text-align:center;" rowspan="2">', 
           '#markup'=>'<b>No certified  </b>',

              '#suffix'=>'</td>',
     
     
           ); 
            $form['step15field']['three'] = array
              (
           '#prefix' => '<td  style="text-align:center;" rowspan="2">', 
           '#markup'=>'<b> No. recertified  </b>',

              '#suffix'=>'</td>',
     
     
           ); 

          $form['step15field']['four'] = array
              (
           '#prefix' => '<td  style="text-align:center;" rowspan="2">', 
           '#markup'=>'<b> No. rejected  </b>',

              '#suffix'=>'</td>',
     
     
           ); 


          $form['step15field']['five'] = array
              (
           '#prefix' => '<td  style="text-align:center;" colspan="3">', 
           '#markup'=>'<b> No. of workers examined under provision of West Bengal Factories rules , 1958   </b>',

              '#suffix'=>'</td></tr>',
     
     
           ); 

           $form['step15field']['six'] = array
              (
           '#prefix' => '<tr> <td  style="text-align:center;" >', 
           '#markup'=>'<b> Nature of Industry   </b>',

              '#suffix'=>'</td>',
     
     
           ); 

            $form['step15field']['seven'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> No of workers examined   </b>',

              '#suffix'=>'</td>',
     
     
           );
            $form['step15field']['eight'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Comments on-fitness   </b>',

              '#suffix'=>'</td></tr>',
     
     
           );

           $form['step15field']['adol'] = array
              (
           '#prefix' => '<tr><td  style="text-align:center;" >', 
           '#markup'=>'<b> Adolescent   </b>',

              '#suffix'=>'</td>',
     
     
           );
           $form['step15field']['adolone'] = array
              (
           '#prefix' => '<td   >', 
           '#type' => 'textfield',
           
           '#suffix'=>'</td>',

            '#default_value' =>$result_step15['adolescent_no_certified']  

         
     
     
           );

        $form['step15field']['adoltwo'] = array
              (
           '#prefix' => '<td   >', 
           '#type' => 'textfield',
           
           '#suffix'=>'</td>',

         '#default_value' =>$result_step15['adolescent_no_recertified']  

         
     
     
           );

               $form['step15field']['adolthree'] = array
              (
           '#prefix' => '<td   >', 
           '#type' => 'textfield',
           
           '#suffix'=>'</td>',

           '#default_value' =>$result_step15['adolescent_no_rejected']  

         
     
     
           );

               $form['step15field']['na_of_ins'] = array
              (
           '#prefix' => '<td rowspan="2"  >', 
           '#type' => 'textfield',
           
           '#suffix'=>'</td>',

        '#default_value' =>$result_step15['nature_of_industry']  

         
     
     
           );

                $form['step15field']['na_of_work'] = array
              (
           '#prefix' => '<td   rowspan="2">', 
           '#type' => 'textfield',
           
           '#suffix'=>'</td>',

          '#default_value' =>$result_step15['no_of_workers_examined']  

         
     
     
           );

                $form['step15field']['comments_on'] = array
              (
           '#prefix' => '<td rowspan="2"   >', 
           '#type' => 'textfield',
           
           '#suffix'=>'</td></tr>',

          '#default_value' =>$result_step15['comments_on_fitness']  

         
     
     
           );

               $form['step15field']['child'] = array
              (
           '#prefix' => '<tr><td >', 
           '#markup'=>'<b>Children </b>',

              '#suffix'=>'</td>',
     
     
           );
              $form['step15field']['child_one'] = array
              (
           '#prefix' => '<td   >', 
           '#type' => 'textfield',
           
           '#suffix'=>'</td>',

          '#default_value' =>$result_step15['children_no_certified']  

         
     
     
           );
               $form['step15field']['child_two'] = array
              (
           '#prefix' => '<td   >', 
           '#type' => 'textfield',
           
           '#suffix'=>'</td>',

           '#default_value' =>$result_step15['children_no_recertified']  

         
     
     
           );

               $form['step15field']['child_three'] = array
              (
           '#prefix' => '<td   >', 
           '#type' => 'textfield',
           
           '#suffix'=>'</td></tr></table>',

           '#default_value' =>$result_step15['children_no_rejected']  

         
     
     
           );

     $form['step15field']['submit_button']                    = array(
                                                                 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
                                                                '#type'                 =>'submit',
                                                                '#value'                =>t(' Save ')
                                                                );

      return $form;

    }

function month_report_step15_submit($form, &$form_state) {
   global $base_root, $base_path,$full_base;

      $full_base='';


      $val=$form_state['values'];
       //print_r($val);
       //exit;


    $monthlyformid=trim($val['monthlyformid']);

       $adolone=trim($val['adolone']);
       $adoltwo=trim($val['adoltwo']);
       $adolthree=trim($val['adolthree']);

       $child_one=trim($val['child_one']);
       $child_two=trim($val['child_two']);
       $child_three=trim($val['child_three']);

       $na_of_ins=trim($val['na_of_ins']);
       $na_of_work=trim($val['na_of_work']);
       $comments_on=trim($val['comments_on']);

    $txn = db_transaction();
      try {
          
   
       $query_update_a_yes=db_query('select  * from labour_factory_statcell_form_5_medical_examination where  monthly_form_id = :filenumber', array(':filenumber' => $monthlyformid));


             
       if($query_update_a_yes->rowCount() > 0) 
          {

      $query_update_B = db_update('labour_factory_statcell_form_5_medical_examination');
      $query_update_B->fields(array(
             'adolescent_no_certified' => $adolone  ,'adolescent_no_recertified' =>$adoltwo ,'adolescent_no_rejected' => $adolthree ,'children_no_certified' =>$child_one ,'children_no_recertified' => $child_two ,'children_no_rejected' => $child_three ,'nature_of_industry' => $na_of_ins ,'no_of_workers_examined' => $na_of_work ,'comments_on_fitness' => $comments_on));
                                        
                                        
                                        
       $query_update_B->condition('monthly_form_id',$monthlyformid);
       $query_update_B->execute(); 

         }
         else
         {

          

 $fieldsA = array('monthly_form_id' => $monthlyformid,  'adolescent_no_certified' => $adolone  ,'adolescent_no_recertified' =>$adoltwo ,'adolescent_no_rejected' => $adolthree ,'children_no_certified' =>$child_one ,'children_no_recertified' => $child_two ,'children_no_rejected' => $child_three ,'nature_of_industry' => $na_of_ins ,'no_of_workers_examined' => $na_of_work ,'comments_on_fitness' => $comments_on );


   db_insert('labour_factory_statcell_form_5_medical_examination')->fields($fieldsA)->execute(); 


   

         }



    
    
       $message = '   data save successfully ';
     drupal_set_message(t($message));
     $full_base=$base_root.$base_path.'admin/monthly-report/step15/'.encryption_decryption_fun('encrypt',$monthlyformid);
               
    drupal_goto($full_base);
    
     }
    catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);
    $message = '    data is not save  ';
     drupal_set_message(t($message));

      $full_base=$base_root.$base_path.'admin/monthly-report/step15/'.encryption_decryption_fun('encrypt',$monthlyformid);
               
    drupal_goto($full_base);
     }


}    