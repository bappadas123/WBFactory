<?php
function month_report_step5( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;

   $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));

    $form['step5field'] = array(
          '#title' => t('<font color="DarkGreen"><b>   Notifiable diseases / Cases of Poisoning  </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          );

$form['step5field']['monthlyformid'] = 
      array('#type' => 'hidden',  
      '#value' => $filenumber,
     
     );

      /* $step5_stepa_query = db_select('labour_factory_statcell_form_5_t5', 'a');
       
        $step5_stepa_query->condition('a.monthly_form_id',trim($filenumber),'=');
      
    
        $step5_stepa_query->fields('a',array('nd_name_of_factory','nd_address_of_factory',
        'nd_nature_mfg_process','nd_persons_involved','nd_persons_involved','nd_occupation','nd_name_of_disease','nd_action_remarks'));
        $step5_stepa_query_result = $step5_stepa_query->execute(); 
    
       $result_step5=$step5_stepa_query_result->fetchAssoc();*/
     $form['step5field']['one'] = array
              (
           '#prefix' => '<table class="table"><tr><td  style="text-align:center;" >', 
           '#markup'=>'<b> Name of <br> the Factory  </b>',

              '#suffix'=>'</td>',
     
     
           ); 

              $form['step5field']['two'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Address of <br> the Factory  </b>',

              '#suffix'=>'</td>',
     
     
           );


               $form['step5field']['three'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Nature of <br>Mfg. process  </b>',

              '#suffix'=>'</td>',
     
     
           );
               $form['step5field']['four'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Name of <br> persons involved  </b>',

              '#suffix'=>'</td>',
     
     
           );

               $form['step5field']['five'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Occupation  </b>',

              '#suffix'=>'</td>',
     
     
           );

               $form['step5field']['six'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Name of the <br> disease / poison  </b>',

              '#suffix'=>'</td>',
     
     
           );
              $form['step5field']['seven'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Action  <br> Taken/ Remarks  </b>',

              '#suffix'=>'</td></tr>',
     
     
           );

              $form['step5field']['onevalue'] = array
              (
           '#prefix' => '<tr> <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
          
     
     
           );
              $form['step5field']['twovalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
         
     
     
           );
               $form['step5field']['threevalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
          
     
     
           );
               $form['step5field']['fourvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
           
     
     
           );
              $form['step5field']['fivevalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
           
     
     
           );
              $form['step5field']['sixvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
         
     
     
           );
              $form['step5field']['sevenvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td></tr></table>',
         
     
     
           );

        $form['step5field']['submit_button']          = array(
                                 
                                 '#prefix' => '<div style="text-align:center;" >',
                                  '#suffix'=>'</div>',  
                                                              
                                '#type'         =>'submit',
                                '#value'        =>t(' Add ')
                                );

           $output1='';
      if(trim($filenumber)){
      $query_tab_1_c=db_query('select  *  from labour_factory_statcell_form_5_t5 where  monthly_form_id = :anid', array(':anid' => trim($filenumber) ));
      if($query_tab_1_c->rowCount() > 0) 
              { 
     $output1 = "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > <th >Name of <br> the Factory</th>
      
       <th > Address of <br>the Factory</th>
      <th >Nature of <br>Mfg. process</th>
       
     <th >Name of <br> persons involved</th>

     <th >Occupation</th>
       
     <th >Name of <br> the disease / poison</th>
      <th >Action <br>Taken/ Remarks</th>
       
     
     <th >DELETE</th>
    </tr>";  
        $i=0;
    foreach($query_tab_1_c as $squan) {
      $i++;
          
          $monthly_form_id = $squan->monthly_form_id; 
          $row_id = $squan->notifiable_desease_id; 
           
              
              
      

         $bb=$base_root.$base_path.'admin/monthly-report-fivedel/'.encryption_decryption_fun('encrypt',$monthly_form_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
    
          $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
    
    
    
          $del_preper=l(t('Delete'),$bb ,array('html'=>TRUE)) ;
        
        
        
              if($i%2==0){
            $output1 .= "<tr bgcolor=\"#FCF6CF\">";
         }
        else
        {
        $output1 .= "<tr bgcolor=\"#FEFEF2\">";
        }
        //$output1.= "<td>".$i."</td>"; 
                $output1.= "<td>".$squan->nd_name_of_factory."</td>";
                 $output1.= "<td>".$squan->nd_address_of_factory."</td>";
                $output1.= "<td>".$squan->nd_nature_mfg_process."</td>";
                $output1.= "<td>".$squan->nd_persons_involved."</td>";
                
             
                $output1.= "<td>".$squan->nd_occupation."</td>";
                $output1.= "<td>".$squan->nd_name_of_disease."</td>";
                $output1.= "<td >".$squan->nd_action_remarks."</td>";
        
       
        $output1.= "<td >".$del_preper."</td>";
      
              
         $output1 .= "</tr>";
            }
              $output1 .= "</table>";
        
      

  
     }
  }
   $form['step5field']['prpersonlista'] = array(
    '#prefix' => '<div align="left" id="step2_part2_div">'.$output1,
    '#suffix' => '</div>',
       
  );




           return $form;
         }

      function month_report_step5_submit($form , $form_state) { 


         global $base_root, $base_path,$full_base;




   $val=$form_state['values'];

 
  $monthly_form_id=trim($val['monthlyformid']); 

 // print $monthly_form_id;  
 // exit; 

  $onevalue=trim($val['onevalue']);  if(!$onevalue) $onevalue= NULL;         
  $twovalue=trim($val['twovalue']); if(!$twovalue) $twovalue= NULL;
  $threevalue=trim($val['threevalue']); if(!$threevalue) $threevalue= NULL;
  $fourvalue=trim($val['fourvalue']); if(!$fourvalue) $fourvalue= NULL;
  $fivevalue=trim($val['fivevalue']); if(!$fivevalue) $fivevalue= NULL;
  $sixvalue=trim($val['sixvalue']); if(!$sixvalue) $sixvalue= NULL;
  $sevenvalue=trim($val['sevenvalue']); if(!$sevenvalue) $sevenvalue= NULL;


  $txn = db_transaction();
    try {


      

  
          $maxresult=db_query('select  max(notifiable_desease_id) maxsl from labour_factory_statcell_form_5_t5'); 
          $result=$maxresult->fetchAssoc();
          $max_sl_number = trim($result['maxsl']); 
        if($max_sl_number==0){$querystring=1; }else{ $querystring=$max_sl_number+1; }
          $rowid=$querystring;

       $fieldsA = array('notifiable_desease_id' => $rowid ,'monthly_form_id' => $monthly_form_id,  'nd_name_of_factory' =>$onevalue,  'nd_address_of_factory' =>$twovalue,'nd_nature_mfg_process' =>$threevalue, 'nd_persons_involved' => $fourvalue, 'nd_occupation' => $fivevalue, 'nd_name_of_disease' => $sixvalue, 'nd_action_remarks' => $sevenvalue);

             db_insert('labour_factory_statcell_form_5_t5')->fields($fieldsA)->execute(); 




   

          

               $full_base=$base_root.$base_path.'admin/monthly-report/step5/'.encryption_decryption_fun('encrypt',$monthly_form_id);

             $message = 'DATA  SAVED SUCCESSFULLY  . ';
                      
       
               drupal_set_message(t($message));
             
               drupal_goto($full_base);

              }
  catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/monthly-report/step5/'.encryption_decryption_fun('encrypt',$monthly_form_id);

             $message = 'DATA NOT SAVED   . ';
                      
       
            drupal_set_message(t($message));
             
          drupal_goto($full_base);
  
     }
   }


   function step5_del(  $filenumber = NULL , $rowid = NULL){
    
   global $base_root, $base_path;
   

     $filenumber=  encryption_decryption_fun('decrypt',trim($filenumber));
     
      $rowid= encryption_decryption_fun('decrypt', trim($rowid));
     // print $filenumber.'ddd'. $rowid;
     // exit;
     
  $txn = db_transaction();
    try {
      
    db_delete('labour_factory_statcell_form_5_t5')
    ->condition('monthly_form_id',trim($filenumber))
    ->condition('notifiable_desease_id',trim($rowid))
    ->execute();
  
  
  $message = '   delete is successfull ';
  
}
  catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);
  $message = '    row is not  delete ';
     }  
  
     //$aa=$base_root.$base_path.'equalremuins/equalinfringements/'.encryption_decryption_fun('encrypt', trim($filenumber));

      $aa=$base_root.$base_path.'admin/monthly-report/step5/'.encryption_decryption_fun('encrypt',$filenumber);
      drupal_set_message(t($message));
     
      drupal_goto($aa);
      
  }

           ?>