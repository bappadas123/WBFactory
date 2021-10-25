<?php
function month_report_step3( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;

   $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));


        $step2_select_query = db_select('labour_factory_statcell_form_5_t3', 'a');
       
        $step2_select_query->condition('a.monthly_form_id',trim($filenumber),'=');
      
    
        $step2_select_query->fields('a',array('ado_id','no_fatal','no_serious','no_explosion','no_fire','no_gassing','no_toxic_release','no_collapse','no_others','visit_fatal','visit_serious','visit_explosion','visit_fire','visit_gassing','visit_toxic_release','visit_collapse','visit_others'));
        $step2_select_query_result = $step2_select_query->execute(); 
    
        $result_step2=$step2_select_query_result->fetchAssoc();

    $form['step3field'] = array(
          '#title' => t('<font color="DarkGreen"><b>  3.Accidents & Dangerous Occurrences  </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          );

      $form['step2field']['monthlyformid'] = 
      array('#type' => 'hidden',  
      '#value' => $filenumber,
     
     );


     $form['step3field']['one'] = array
              (
           '#prefix' => '<table class="table"><tr><td colspan="2" style="text-align:center;" >', 
           '#markup'=>'<b> No. Of Accidents  </b>',

              '#suffix'=>'</td>',
     
     
           ); 

               $form['step3field']['two'] = array
              (
           '#prefix' => '<td colspan="6" style="text-align:center;" >', 
           '#markup'=>'<b> No. of dangerous occurrences  </b>',

              '#suffix'=>'</td>',
     
     
           ); 
               $form['step3field']['three'] = array
              (
           '#prefix' => '<td colspan="8" style="text-align:center;" >', 
           '#markup'=>'<b> No. of visits paid in connection with  </b>',

              '#suffix'=>'</td></tr>',
     
     
           ); 

              $form['step3field']['oneone'] = array
              (
           '#prefix' => '<tr><td  style="text-align:center;" >', 
           '#markup'=>'<b> Fatal  </b>',

              '#suffix'=>'</td>',
     
     
           );

              $form['step3field']['onetwo'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Serious  </b>',

              '#suffix'=>'</td>',
     
     
           );
               $form['step3field']['twoone'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Explosion  </b>',

              '#suffix'=>'</td>',
     
     
           );
               $form['step3field']['twotwo'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Fire  </b>',

              '#suffix'=>'</td>',
     
     
           );
               $form['step3field']['twothree'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Gassing  </b>',

              '#suffix'=>'</td>',
     
     
           );
               $form['step3field']['twofour'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Toxic Release  </b>',

              '#suffix'=>'</td>',
     
     
           );
              $form['step3field']['twofive'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Collapse  </b>',

              '#suffix'=>'</td>',
     
     
           );
              $form['step3field']['twosix'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Others  </b>',

              '#suffix'=>'</td>',
     
     
           );
              $form['step3field']['threeone'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Fatal accident  </b>',

              '#suffix'=>'</td>',
     
     
           );
              $form['step3field']['threetwo'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Serious accident  </b>',

              '#suffix'=>'</td>',
     
     
           );
              $form['step3field']['threefour'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Explosion  </b>',

              '#suffix'=>'</td>',
     
     
           );
              $form['step3field']['threefive'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Fire  </b>',

              '#suffix'=>'</td>',
     
     
           );
              

              $form['step3field']['threesix'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Gassing  </b>',

              '#suffix'=>'</td>',
     
     
           );
              $form['step3field']['threeseven'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Toxic release  </b>',

              '#suffix'=>'</td>',
     
     
           );
              $form['step3field']['threeeight'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Collapse  </b>',

              '#suffix'=>'</td>',
     
     
           );
              $form['step3field']['threenine'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Others  </b>',

              '#suffix'=>'</td></tr>',
     
     
           );
               $form['step3field']['oneonevalue'] = array
              (
           '#prefix' => ' <tr> <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step2['no_fatal']
     
     
           ); 
               $form['step3field']['onetwovalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
              '#default_value' =>$result_step2['no_serious']
     
     
           ); 
              $form['step3field']['twoonevalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
              '#default_value' =>$result_step2['no_explosion']
     
     
           );
              $form['step3field']['twotwovalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' =>8,

            '#suffix'=>'</td>',
              '#default_value' =>$result_step2['no_fire']
     
     
           );
           $form['step3field']['twothreevalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step2['no_gassing']
     
     
           ); 
            $form['step3field']['twofourvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step2['no_toxic_release']
     
     
           ); 
           $form['step3field']['twofivevalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
              '#default_value' =>$result_step2['no_collapse']
     
     
           ); 
           $form['step3field']['twosixvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
            '#default_value' =>$result_step2['no_others']
     
     
           );  
              $form['step3field']['threeonevalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step2['visit_fatal']
     
     
           ); 
              $form['step3field']['threetwovalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
            '#default_value' =>$result_step2['visit_serious']
     
     
           ); 
              $form['step3field']['threethreevalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
             '#default_value' =>$result_step2['visit_explosion']
     
     
           ); 
              $form['step3field']['threefourvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
                '#default_value' =>$result_step2['visit_fire']
     
     
           );
              $form['step3field']['threefivevalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
            '#default_value' =>$result_step2['visit_gassing']
     
     
           );
               $form['step3field']['threesixvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
            '#default_value' =>$result_step2['visit_toxic_release']
     
     
           );
              $form['step3field']['threesevenvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
          '#size' => 5,

          '#suffix'=>'</td>',
          '#default_value' =>$result_step2['visit_collapse']
     
     
           );
               $form['step3field']['threeeightvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
            '#size' => 5,

            '#suffix'=>'</td></tr></table>',
             '#default_value' =>$result_step2['visit_others']
     
     
           );


              $form['step3field']['submit_button']          = array(
                                 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
                                '#type'         =>'submit',
                                '#value'        =>t(' Save ')
                                );

             return $form; 

     }

     function month_report_step3_submit($form , $form_state) { 


         global $base_root, $base_path,$full_base;




$val=$form_state['values'];
//print_r($val);  
//exit;
 
  $monthly_form_id=trim($val['monthlyformid']); 

 // print $monthly_form_id;  
 // exit; 

  $oneonevalue=trim($val['oneonevalue']);  if(!$oneonevalue) $oneonevalue= NULL;         
  $onetwovalue=trim($val['onetwovalue']); if(!$onetwovalue) $onetwovalue= NULL;

  $twoonevalue=trim($val['twoonevalue']); if(!$twoonevalue) $twoonevalue= NULL;
  $twotwovalue=trim($val['twotwovalue']); if(!$twotwovalue) $twotwovalue= NULL;
  $twothreevalue=trim($val['twothreevalue']); if(!$twothreevalue) $twothreevalue= NULL;
  $twofourvalue=trim($val['twofourvalue']);  if(!$twofourvalue) $twofourvalue= NULL;         
  $twofivevalue=trim($val['twofivevalue']); if(!$twofivevalue) $twofivevalue= NULL;
  $twosixvalue=trim($val['twosixvalue']); if(!$twosixvalue) $twosixvalue= NULL;



  

  $threeonevalue=trim($val['threeonevalue']); if(!$threeonevalue) $threeonevalue= NULL;
  $threetwovalue=trim($val['threetwovalue']); if(!$threetwovalue) $threetwovalue= NULL;
  $threethreevalue=trim($val['threethreevalue']);   if(!$threethreevalue) $threethreevalue= NULL;
  $threefourvalue=trim($val['threefourvalue']); if(!$threefourvalue) $threefourvalue= NULL;
  $threefivevalue=trim($val['threefivevalue']); if(!$threefivevalue) $threefivevalue= NULL;

   $threesixvalue=trim($val['threesixvalue']); if(!$threesixvalue) $threesixvalue= NULL;
   $threesevenvalue=trim($val['threesevenvalue']); if(!$threesevenvalue) $threesevenvalue= NULL;
   $threeeightvalue=trim($val['threeeightvalue']); if(!$threeeightvalue) $threeeightvalue= NULL;
  


   $txn = db_transaction();
    try {


       $query_update_yes=db_query('select  * from labour_factory_statcell_form_5_t3 where  monthly_form_id = :filenumber', array(':filenumber' => $monthly_form_id));


             
       if($query_update_yes->rowCount() > 0) 
          {
             
        $query_update_A = db_update('labour_factory_statcell_form_5_t3');
        $query_update_A->fields(array(
     'no_fatal' =>$oneonevalue,  'no_serious' =>$onetwovalue,'no_explosion' =>$twoonevalue, 'no_fire' => $twotwovalue, 'no_gassing' => $twothreevalue, 'no_toxic_release' => $twofourvalue, 'no_collapse' => $twofivevalue, 'no_others' => $twosixvalue, 'visit_fatal' => $threeonevalue,


    'visit_serious' => $threetwovalue, 'visit_explosion' => $threethreevalue , 'visit_fire' => $threefourvalue
     , 'visit_gassing' => $threefivevalue , 'visit_toxic_release' => $threesixvalue , 'visit_collapse' => $threesevenvalue ,

     'visit_others' => $threeeightvalue




   ));
                    
                    
                    
       $query_update_A->condition('monthly_form_id',$monthly_form_id);
       $query_update_A->execute();  

          }
          else

          {

  
            $maxresult=db_query('select  max(ado_id) maxsl from labour_factory_statcell_form_5_t3'); 
          $result=$maxresult->fetchAssoc();
          $max_sl_number = trim($result['maxsl']); 
            if($max_sl_number==0){$querystring=1; }else{ $querystring=$max_sl_number+1; }
        $rowid=$querystring;

 $fieldsA = array('ado_id' => $rowid ,'monthly_form_id' => $monthly_form_id, 'no_fatal' =>$oneonevalue,  'no_serious' =>$onetwovalue,'no_explosion' =>$twoonevalue, 'no_fire' => $twotwovalue, 'no_gassing' => $twothreevalue, 'no_toxic_release' => $twofourvalue, 'no_collapse' => $twofivevalue, 'no_others' => $twosixvalue, 'visit_fatal' => $threeonevalue,


    'visit_serious' => $threetwovalue, 'visit_explosion' => $threethreevalue , 'visit_fire' => $threefourvalue
     , 'visit_gassing' => $threefivevalue , 'visit_toxic_release' => $threesixvalue , 'visit_collapse' => $threesevenvalue ,

     'visit_others' => $threeeightvalue );

             db_insert('labour_factory_statcell_form_5_t3')->fields($fieldsA)->execute(); 




   

             }

            $full_base=$base_root.$base_path.'admin/monthly-report/step3/'.encryption_decryption_fun('encrypt',$monthly_form_id);

             $message = 'DATA  SAVED SUCCESSFULLY  . ';
                      
       
                      drupal_set_message(t($message));
             
               drupal_goto($full_base);

              }
  catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/monthly-report/step3/'.encryption_decryption_fun('encrypt',$monthly_form_id);

             $message = 'DATA NOT SAVED   . ';
                      
       
                      drupal_set_message(t($message));
             
               drupal_goto($full_base);
  
     }
  }
     ?>
   