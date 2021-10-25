<?php
function month_report_step11( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;

    $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));

    $form['step11field'] = array(
          '#title' => t('<font color="DarkGreen"><b>    </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          );


         $mr_elevenquery = db_select('labour_factory_statcell_form_5', 'a');
       
        $mr_elevenquery->condition('a.monthly_form_id',trim($filenumber),'=');
      
    
        $mr_elevenquery->fields('a',array('appeal_to_high_court','other_mat_special_interest'));
        $mr_elevenquery_result = $mr_elevenquery->execute(); 
    
       $result_elevenq=$mr_elevenquery_result->fetchAssoc();
       $appeal_to_high_court=$result_elevenq['appeal_to_high_court'];
       $other_mat_special_interest=$result_elevenq['other_mat_special_interest'];
     
  
    

   
   $form['step11field']['inspectionid'] = 
      array('#type' => 'hidden',  
      '#value' => $filenumber,
     
     );

     $form['step11field']['one'] = array
              (
           '#prefix' => '<table class="table"><tr><td   >', 
           '#markup'=>'<b> 11. Particulars of Appeal to High Court :  </b>',

              '#suffix'=>'</td>',
     
     
           ); 

       $form['step11field']['oneValue'] = array
              (
           '#prefix' => '<td style="text-align:left;"       >', 
          '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

          '#suffix'=>'</td></tr>',
           '#default_value' =>$appeal_to_high_court
     
     
           );


           $form['step11field']['two'] = array
              (
           '#prefix' => '<tr><td  >', 
           '#markup'=>'<b> 14. Other matters of special interest :  </b>',

            '#suffix'=>'</td>',
     
     
           );
             $form['step11field']['twoValue'] = array
              (
           '#prefix' => '<td style="text-align:left;"       >', 
          '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,
             '#default_value' =>$other_mat_special_interest,

          '#suffix'=>'</td></tr></table>',
     
     
           );
            $form['step11field']['submit_button']          = array(
                                 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
                                '#type'         =>'submit',
                                '#value'        =>t(' Save ')
                                );

           return $form;
         }

    function month_report_step11_submit($form , $form_state) {  

                global $base_root, $base_path,$full_base;

     $full_base='';


          $val=$form_state['values'];
        


    $monthlyid=trim($val['inspectionid']);
    //part A
  $colD1=trim($val['oneValue']); if(!$colD1)  $colD1= NULL;   
  $colD2=trim($val['twoValue']); if(!$colD2)  $colD2= NULL;   


     $txn = db_transaction();
    try {

                  $query_update_a_yes=db_query('select  * from labour_factory_statcell_form_5 where  monthly_form_id = :filenumber', array(':filenumber' => $monthlyid));


             
    
       if($query_update_a_yes->rowCount() > 0 ) {
       
         $query_update_B = db_update('labour_factory_statcell_form_5');
      $query_update_B->fields(array(
      'appeal_to_high_court' =>$colD1, 'other_mat_special_interest' => $colD2));
                    
                    
                    
       $query_update_B->condition('monthly_form_id',$monthlyid);
       $query_update_B->execute(); 
        $full_base=$base_root.$base_path.'admin/monthly-report/step11/'.encryption_decryption_fun('encrypt',$monthlyid);

       $message = 'DATA   IS SAVE SUCCESSFULLY  . ';

        }
        



     }
  catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

   $full_base=$base_root.$base_path.'admin/monthly-report/step11/'.encryption_decryption_fun('encrypt',$monthlyid);

             $message = 'DATA  IS NOT SAVED  . ';
                      
       
  
     } 


                drupal_set_message(t($message));
             
               drupal_goto($full_base); 

 }

           ?>