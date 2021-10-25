<?php
function month_report_step10( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;

   $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));

     drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
     drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');


     $get_info_montly_report=get_monthly_area_from_to_date($filenumber);

    $form['step10field'] = array(
          '#title' => t('<font color="DarkGreen">'.$get_info_montly_report.'<b>   Particulars of the cases disposed off  </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          );

          $form['step10field']['monthlyformid'] = 
         array('#type' => 'hidden',  
         '#value' => $filenumber,
     
        );


     $form['step10field']['one'] = array
              (
           '#prefix' => '<table class="table"><tr><td  style="text-align:center;"  >', 
           '#markup'=>'<b> Name <br>of the Factory  </b>',

              '#suffix'=>'</td>',
     
     
           ); 

       $form['step10field']['two'] = array
              (
           '#prefix' => '<td  style="text-align:center;"    >', 
           '#markup'=>'<b> Address <br> of the Factory  </b>',

              '#suffix'=>'</td>',
     
     
           );


           $form['step10field']['three'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Person Prosecuted <br> (Occupier, <br> Manager etc)  </b>',

              '#suffix'=>'</td>',
     
     
           );

            $form['step10field']['four'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Case No.  </b>',

              '#suffix'=>'</td>',
     
     
           );
            
            $form['step10field']['five'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Name <br> of the act </b>',

              '#suffix'=>'</td>',
     
     
           ); 
            $form['step10field']['six'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Violation  </b>',

              '#suffix'=>'</td>',
     
     
           ); 
            $form['step10field']['seven'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Result/ Amount <br> of the fine  </b>',

              '#suffix'=>'</td>',
     
     
           ); 
           $form['step10field']['eight'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Date <br>of disposal  </b>',

              '#suffix'=>'</td>',
     
     
           );  
            $form['step10field']['nine'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Name <br>of the Court    </b>',

              '#suffix'=>'</td>',
     
     
           );  
            $form['step10field']['ten'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Remarks <br>/ Result  </b>',

              '#suffix'=>'</td></tr>',
     
     
           );  

            $form['step10field']['onevalue'] = array
              (
           '#prefix' => '<tr> <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
     
     
           ); 
           $form['step10field']['twovalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
     
     
           ); 
           

            $form['occupier_option'] = array(
         '#type' => 'value',
         '#value' => array('0'=>t('select'),'Occupier'=>t('Occupier'),'Manager'=>t('Manager'),'occupier-manager'=>t('Occupier-Manager'))
     
    
         );
            
            $form['step10field']['threevalue'] = array
              (
           '#prefix' => ' <td>', 
              '#type' => 'select',
          '#options' => $form['occupier_option']['#value'],

            '#suffix'=>'</td>',
     
     
           ); 
           $form['step10field']['fourvalue'] = array
              (
           '#prefix' => ' <td  >', 
              '#type' => 'textfield',
                '#size' => 10,

            '#suffix'=>'</td>',
     
     
           );  
            $form['step10field']['fivevalue'] = array
              (
           '#prefix' => ' <td  >', 
              '#type' => 'textfield',
                '#size' => 10,

            '#suffix'=>'</td>',
     
     
           ); 
            $form['step10field']['sixvalue'] = array
              (
           '#prefix' => ' <td  >', 
             

            '#type' => 'textarea',
           
            '#rows' => 6,
            '#cols' => 6,

            '#suffix'=>'</td>',
     
     
           );
             $form['step10field']['sevenvalue'] = array
              (
           '#prefix' => ' <td  >', 
              '#type' => 'textfield',
                '#size' => 10,

            '#suffix'=>'</td>',
     
     
           );  
            $form['step10field']['eightvalue'] = array
              (
           '#prefix' => ' <td  >', 
              '#type' => 'textfield',
             '#size' => 12,
            '#attributes' => array('class' => array('datepicker_retify')),

            '#suffix'=>'</td>',
     
     
           );  
            $form['step10field']['ninevalue'] = array
              (
           '#prefix' => ' <td  >', 
              '#type' => 'textfield',
                '#size' => 10,

            '#suffix'=>'</td>',
     
     
           ); 
            $form['step10field']['tenvalue'] = array
              (
           '#prefix' => ' <td  >', 
            '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td></tr></table>',
     
     
           );  
             
          $form['step10field']['submit_button']          = array(
                                 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
                                '#type'         =>'submit',
                                '#value'        =>t(' Save ')
                                );
      
       

           
          $output1='';
      if(trim($filenumber)){
      $query_tab_1_c=db_query('select  *  from labour_factory_statcell_form_5_t10_7_t7 where  monthly_form_id = :anid', array(':anid' => trim($filenumber) ));
      if($query_tab_1_c->rowCount() > 0) 
              { 
     $output1 = "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > <th >Name <br>of the Factory</th>
      
       <th > Address <br>of the Factory</th>
      
       
     <th >Person Prosecuted <br>(Occupier, Manager etc)</th>

    

     <th >Case No.</th>
      <th >Name <br>of the act.</th>
      <th >Violation.</th>
      <th >Result/ <br>Amount of the fine</th>
      <th >Date <br>of disposal</th>
      <th >Name <br>of the Court</th>
      <th >Remarks <br>/ Result</th>
    
       
     
     <th >DELETE</th>
    </tr>";  
        $i=0;
    foreach($query_tab_1_c as $squan) {
      $i++;
          
          $monthly_form_id = $squan->monthly_form_id; 
          $row_id = $squan->case_disposed_id; 
         
           
              
              
      

         $bb=$base_root.$base_path.'admin/monthly-report-tendel/'.encryption_decryption_fun('encrypt',$monthly_form_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
    
          $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
    
    
    
          $del_preper=l(t('Delete'),$bb ,array('html'=>TRUE)) ;
        
        
        
              if($i%2==0){
            $output1 .= "<tr bgcolor=\"#FCF6CF\">";
         }
        else
        {
        $output1 .= "<tr bgcolor=\"#FEFEF2\">";
        }
      
                $output1.= "<td>".$squan->case_disposed_name_of_factory."</td>";
                $output1.= "<td>".$squan->case_disposed_address_of_factory."</td>";
                $output1.= "<td>".$squan->case_disposed_person_prosecuted."</td>";
                $output1.= "<td>".$squan->case_disposed_case_no."</td>";
                $output1.= "<td>".$squan->case_disposed_name_of_act."</td>";
                $output1.= "<td>".$squan->case_disposed_violation."</td>";
                $output1.= "<td>".$squan->case_disposed_result_fine."</td>";
                $output1.= "<td>".date('d-m-Y', strtotime($squan->case_disposed_date_of_disposal))."</td>";
                $output1.= "<td>".$squan->case_disposed_name_of_court."</td>";
                $output1.= "<td>".$squan->case_disposed_remarks_result."</td>";
                $output1.= "<td >".$del_preper."</td>";
               
                
        
       
            
      
              
         $output1 .= "</tr>";
            }
              $output1 .= "</table>";
        
      

  
     }
  }
        $form['step10field']['prpersonlista'] = array(
       '#prefix' => '<div align="left" id="step2_part2_div">'.$output1,
       '#suffix' => '</div>',
       
      );

          
      
        
          
      
       
           
        

           return $form;
         }

         function month_report_step10_submit($form , $form_state) { 


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

  $sixvalue=trim($val['sixvalue']);  if(!$sixvalue) $sixvalue= NULL;         
  $sevenvalue=trim($val['sevenvalue']); if(!$sevenvalue) $sevenvalue= NULL;
  $eightvalue=trim($val['eightvalue']); 
  if(!$eightvalue) 
    $eightvalue= NULL;
  else
   $eightvalue= date('Y-m-d', strtotime($eightvalue));    
  $ninevalue=trim($val['ninevalue']); if(!$ninevalue) $ninevalue= NULL;
  $tenvalue=trim($val['tenvalue']); if(!$tenvalue) $tenvalue= NULL;
  

  $txn = db_transaction();
    try {


      

  
          $maxresult=db_query('select  max(case_disposed_id) maxsl from labour_factory_statcell_form_5_t10_7_t7'); 
          $result=$maxresult->fetchAssoc();
          $max_sl_number = trim($result['maxsl']); 
          if($max_sl_number==0){$querystring=1; }else{ $querystring=$max_sl_number+1; }
          $rowid=$querystring;

       $fieldsA = array('case_disposed_id' => $rowid ,'monthly_form_id' => $monthly_form_id, 'form_type'=>'GENERAL','case_disposed_name_of_factory'=> $onevalue , 'case_disposed_address_of_factory' =>$twovalue,  'case_disposed_person_prosecuted' =>$threevalue,'case_disposed_case_no' =>$fourvalue, 'case_disposed_name_of_act' => $fivevalue, 'case_disposed_violation' => $sixvalue, 'case_disposed_result_fine' => $sevenvalue, 'case_disposed_date_of_disposal' => $eightvalue, 'case_disposed_name_of_court' => $ninevalue,'case_disposed_remarks_result' => $tenvalue);

             db_insert('labour_factory_statcell_form_5_t10_7_t7')->fields($fieldsA)->execute(); 




   

          

               $full_base=$base_root.$base_path.'admin/monthly-report/step10/'.encryption_decryption_fun('encrypt',$monthly_form_id);

             $message = 'DATA  SAVED SUCCESSFULLY  . ';
                      
       
               drupal_set_message(t($message));
             
               drupal_goto($full_base);

              }
  catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/monthly-report/step10/'.encryption_decryption_fun('encrypt',$monthly_form_id);

             $message = 'DATA NOT SAVED   . ';
                      
       
            drupal_set_message(t($message));
             
          drupal_goto($full_base);
  
     }
   }



      function step10_del(  $filenumber = NULL , $rowid = NULL){
    
   global $base_root, $base_path;
    

     $filenumber=  encryption_decryption_fun('decrypt',trim($filenumber));
     
      $rowid=  encryption_decryption_fun('decrypt',trim($rowid));
     // print $filenumber.'ddd'. $rowid;
     // exit;
     
  $txn = db_transaction();
    try {
      
    db_delete('labour_factory_statcell_form_5_t10_7_t7')
    ->condition('monthly_form_id',trim($filenumber))
    ->condition('case_disposed_id',trim($rowid))
    ->execute();
  
  
  $message = '   delete is successfull ';
  
}
  catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);
  $message = '    row is not  delete ';
     }  
  
     //$aa=$base_root.$base_path.'equalremuins/equalinfringements/'.encryption_decryption_fun('encrypt', trim($filenumber));

      $aa=$base_root.$base_path.'admin/monthly-report/step10/'.encryption_decryption_fun('encrypt',$filenumber);
      drupal_set_message(t($message));
     
      drupal_goto($aa);
      
  }

           ?>