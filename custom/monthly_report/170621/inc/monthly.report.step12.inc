<?php
function month_report_step12( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;

     $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));

     drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
     drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');

     $get_info_montly_report=get_monthly_area_from_to_date($filenumber);

    $form['step12field'] = array(
          '#title' => t('<font color="DarkGreen">'.$get_info_montly_report.'<b>  Details of Seminars/Training Courses etc.   </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          );
   $form['step12field']['monthlyformid'] = 
         array('#type' => 'hidden',  
         '#value' => $filenumber,
     
        );


     $form['step12field']['one'] = array
              (
           '#prefix' => '<table class="table"><tr><td   >', 
           '#markup'=>'<b> Name of the Factory  </b>',

              '#suffix'=>'</td>',
     
     
           ); 


           $form['step12field']['two'] = array
              (
           '#prefix' => '<td  >', 
           '#markup'=>'<b> Address of the Factory  </b>',

              '#suffix'=>'</td>',
     
     
           );
             
     $form['step12field']['three'] = array
              (
           '#prefix' => '<td  >', 
           '#markup'=>'<b> Type of program  </b>',

              '#suffix'=>'</td>',
     
     
           );
             $form['step12field']['four'] = array
              (
           '#prefix' => '<td  >', 
           '#markup'=>'<b> Date of program  </b>',

              '#suffix'=>'</td>',
     
     
           );

           $form['step12field']['five'] = array
              (
           '#prefix' => '<td  >', 
           '#markup'=>'<b> No. of participants  </b>',

              '#suffix'=>'</td>',
     
     
           );

            $form['step12field']['six'] = array
              (
           '#prefix' => '<td  >', 
           '#markup'=>'<b> Status of participants  </b>',

              '#suffix'=>'</td></tr>',
     
     
           );

           $form['step12field']['onevalue'] = array
              (
           '#prefix' => '<tr> <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
     
     
           ); 
           $form['step12field']['twovalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
     
     
           ); 
           $form['step12field']['threevalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
     
     
           ); 
           $form['step12field']['fourvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 12,
                 '#attributes' => array('class' => array('datepicker_retify')),

            '#suffix'=>'</td>',
     
     
           );
           $form['step12field']['fivevalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
                '#size' => 5,

            '#suffix'=>'</td>',
            '#element_validate' => array('MONTHLY_MANDATORY_INTEGER_CHECKING_validate'),
     
     
           );
            $form['step12field']['sixvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td></tr></table>',
     
     
           ); 
            $form['step12field']['submit_button']          = array(
                                 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
                                                               '#type'    =>'submit',
                                                               '#value'  =>t(' ADD ')
                                );

                $output1='';
      if(trim($filenumber)){
      $query_tab_1_c=db_query('select  *  from labour_factory_statcell_form_5_t12_6_t5_7_t5 where  monthly_form_id = :anid', array(':anid' => trim($filenumber) ));
      if($query_tab_1_c->rowCount() > 0) 
              { 
     $output1 = "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > <th >Name of the Factory</th>
      
       <th > Address of the Factory</th>
      
       
     <th >Type of program</th>

    

     <th >Date of program</th>
      <th >No. of participants</th>
      <th >Status of participants</th>
    
    
       
     
     <th >DELETE</th>
    </tr>";  
        $i=0;
    foreach($query_tab_1_c as $squan) {
      $i++;
          
          $monthly_form_id = $squan->monthly_form_id; 
          $row_id = $squan->seminar_id; 
         
           
              
              
      

         $bb=$base_root.$base_path.'admin/monthly-report-twelvevdel/'.encryption_decryption_fun('encrypt',$monthly_form_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
    
          $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
    
    
    
          $del_preper=l(t('Delete'),$bb ,array('html'=>TRUE)) ;
        
        
        
              if($i%2==0){
            $output1 .= "<tr bgcolor=\"#FCF6CF\">";
         }
        else
        {
        $output1 .= "<tr bgcolor=\"#FEFEF2\">";
        }
      
                $output1.= "<td>".$squan->seminar_name_of_factory."</td>";
                $output1.= "<td>".$squan->seminar_address_of_factory."</td>";
                $output1.= "<td>".$squan->seminar_type_of_program."</td>";
                $output1.= "<td>".date('d-m-Y', strtotime($squan->seminar_date_of_program))."</td>";
                $output1.= "<td>".$squan->seminar_no_of_participants."</td>";
                $output1.= "<td>".$squan->seminar_status_of_participants."</td>";
             
                $output1.= "<td >".$del_preper."</td>";
               
                
        
       
            
      
              
         $output1 .= "</tr>";
            }
              $output1 .= "</table>";
        
      

  
     }
  }
        $form['step12field']['prpersonlista'] = array(
       '#prefix' => '<div align="left" id="step2_part2_div">'.$output1,
       '#suffix' => '</div>',
       
      );




           return $form;
         }

           function step12_del(  $filenumber = NULL , $rowid = NULL){
    
      global $base_root, $base_path;
    

     $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));
     
      $rowid=  encryption_decryption_fun('decrypt',trim($rowid));
     // print $filenumber.'ddd'. $rowid;
     // exit;
     
  $txn = db_transaction();
    try {
      
    db_delete('labour_factory_statcell_form_5_t12_6_t5_7_t5')
    ->condition('monthly_form_id',trim($filenumber))
    ->condition('seminar_id',trim($rowid))
    ->execute();
  
  
  $message = '   delete is successfull ';
  
}
  catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);
  $message = '    row is not  delete ';
     }  
  
     //$aa=$base_root.$base_path.'equalremuins/equalinfringements/'.encryption_decryption_fun('encrypt', trim($filenumber));

      $aa=$base_root.$base_path.'admin/monthly-report/step12/'.encryption_decryption_fun('encrypt',$filenumber);
      drupal_set_message(t($message));
     
      drupal_goto($aa);
      
  }


  function month_report_step12_submit($form , $form_state) { 


         global $base_root, $base_path,$full_base;




   $val=$form_state['values'];

 
  $monthly_form_id=trim($val['monthlyformid']); 

 // print $monthly_form_id;  
 // exit; 

  $onevalue=trim($val['onevalue']);  if(!$onevalue) $onevalue= NULL;         
  $twovalue=trim($val['twovalue']); if(!$twovalue) $twovalue= NULL;
  $threevalue=trim($val['threevalue']); if(!$threevalue) $threevalue= NULL;
  $fourvalue=trim($val['fourvalue']); 
  if(!$fourvalue) 
    $fourvalue= NULL;
  else
     $fourvalue= date('Y-m-d', strtotime($fourvalue));    

  $fivevalue=trim($val['fivevalue']); if(!$fivevalue) $fivevalue= NULL;
   $sixvalue=trim($val['sixvalue']); if(!$sixvalue) $sixvalue= NULL;

 
  

  $txn = db_transaction();
    try {


      

  
          $maxresult=db_query('select  max(seminar_id) maxsl from labour_factory_statcell_form_5_t12_6_t5_7_t5'); 
          $result=$maxresult->fetchAssoc();
          $max_sl_number = trim($result['maxsl']); 
          if($max_sl_number==0){$querystring=1; }else{ $querystring=$max_sl_number+1; }
          $rowid=$querystring;

       $fieldsA = array('seminar_id' => $rowid ,'monthly_form_id' => $monthly_form_id, 'form_type'=>'GENERAL','seminar_name_of_factory'=> $onevalue , 'seminar_address_of_factory' =>$twovalue,  'seminar_type_of_program' =>$threevalue,'seminar_date_of_program' =>$fourvalue, 'seminar_no_of_participants' => $fivevalue, 'seminar_status_of_participants' => $sixvalue);

             db_insert('labour_factory_statcell_form_5_t12_6_t5_7_t5')->fields($fieldsA)->execute(); 




   

          

               $full_base=$base_root.$base_path.'admin/monthly-report/step12/'.encryption_decryption_fun('encrypt',$monthly_form_id);

             $message = 'DATA  SAVED SUCCESSFULLY  . ';
                      
       
               drupal_set_message(t($message));
             
               drupal_goto($full_base);

              }
  catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/monthly-report/step12/'.encryption_decryption_fun('encrypt',$monthly_form_id);

             $message = 'DATA NOT SAVED   . ';
                      
       
            drupal_set_message(t($message));
             
          drupal_goto($full_base);
  
     }
   }


           ?>