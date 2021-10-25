<?php
function month_report_step9( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;

   $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));

   $get_info_montly_report=get_monthly_area_from_to_date($filenumber);


    $form[''] = array(
          '#title' => t('<font color="DarkGreen">'.$get_info_montly_report.'<b>   Prosecution Proceedings instituted  </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          );

       $form['step9field']['monthlyformid'] = 
         array('#type' => 'hidden',  
         '#value' => $filenumber,
     
        );
   


     $form['step9field']['one'] = array
              (
           '#prefix' => '<table class="table"><tr><td  style="text-align:center;"  >', 
           '#markup'=>'<b> Name <br>of the Factory  </b>',

              '#suffix'=>'</td>',
     
     
           ); 

       $form['step9field']['two'] = array
              (
           '#prefix' => '<td  style="text-align:center;"    >', 
           '#markup'=>'<b> Address <br>of the Factory  </b>',

              '#suffix'=>'</td>',
     
     
           );


           $form['step9field']['three'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Registered<br>/Unregistered  </b>',

              '#suffix'=>'</td>',
     
     
           );

            $form['step9field']['four'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Person <br>Prosecuted <br>(Occupier, Manager etc)  </b>',

              '#suffix'=>'</td>',
     
     
           );
            
            $form['step9field']['five'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Case No.  </b>',

              '#suffix'=>'</td>',
     
     
           ); 
            $form['step9field']['six'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Name <br>of the act  </b>',

              '#suffix'=>'</td>',
     
     
           ); 
            $form['step9field']['seven'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Violation  </b>',

              '#suffix'=>'</td>',
     
     
           ); 
           $form['step9field']['eight'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Penal <br>Provision  </b>',

              '#suffix'=>'</td>',
     
     
           );  
            $form['step9field']['nine'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Name <br>of the Court  </b>',

              '#suffix'=>'</td>',
     
     
           );  
            $form['step9field']['ten'] = array
              (
           '#prefix' => '<td  style="text-align:center;" >', 
           '#markup'=>'<b> Remarks <br>/ Result  </b>',

              '#suffix'=>'</td></tr>',
     
     
           );  

            $form['step9field']['onevalue'] = array
              (
           '#prefix' => '<tr> <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
     
     
           ); 
           $form['step9field']['twovalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
     
     
           ); 
            $form['reg_option'] = array(
         '#type' => 'value',
         '#value' => array('0'=>t('select'),'Registered'=>t('Registered'),'Unregistered'=>t('Unregistered'))
     
    
         );
  
  
  


            
              $form['step9field']['threevalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'select',
              '#options' => $form['reg_option']['#value'],

            '#suffix'=>'</td>',
     
     
           );

            $form['occupier_option'] = array(
         '#type' => 'value',
         '#value' => array('0'=>t('select'),'Occupier'=>t('Occupier'),'Manager'=>t('Manager'),'occupier-manager'=>t('Occupier-Manager'))
     
    
         );
            
            $form['step9field']['fourvalue'] = array
              (
           '#prefix' => ' <td>', 
              '#type' => 'select',
          '#options' => $form['occupier_option']['#value'],

            '#suffix'=>'</td>',
     
     
           ); 
           $form['step9field']['fivevalue'] = array
              (
           '#prefix' => ' <td  >', 
              '#type' => 'textfield',
                '#size' => 10,

            '#suffix'=>'</td>',
     
     
           );  
            $form['step9field']['sixvalue'] = array
              (
           '#prefix' => ' <td  >', 
              '#type' => 'textfield',
                '#size' => 10,

            '#suffix'=>'</td>',
     
     
           );
             $form['step9field']['sevenvalue'] = array
              (
           '#prefix' => ' <td  >', 
             // '#type' => 'textfield',
             //   '#size' => 10,

               '#type' => 'textarea',
           
                '#rows' => 5,
                 '#cols' => 5,


            '#suffix'=>'</td>',
     
     
           );  
            $form['step9field']['eightvalue'] = array
              (
           '#prefix' => ' <td  >', 
              '#type' => 'textfield',
                '#size' => 10,

            '#suffix'=>'</td>',
     
     
           );  
            $form['step9field']['ninevalue'] = array
              (
           '#prefix' => ' <td  >', 
              '#type' => 'textfield',
                '#size' => 10,

            '#suffix'=>'</td>',
     
     
           ); 
            $form['step9field']['tenvalue'] = array
              (
           '#prefix' => ' <td  >', 
            '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td></tr></table>',
     
     
           );  
             
          $form['step9field']['submit_button']          = array(
                                 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
                                '#type'         =>'submit',
                                '#value'        =>t(' Save ')
                                );
      
       

           
          
$output1='';
      if(trim($filenumber)){
      $query_tab_1_c=db_query('select  *  from labour_factory_statcell_form_5_t9_7_t6 where  monthly_form_id = :anid', array(':anid' => trim($filenumber) ));
      if($query_tab_1_c->rowCount() > 0) 
              { 
     $output1 = "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > <th >Name <br>of the Factory</th>
      
       <th > Address <br>of the Factory</th>
      <th >Registered/<br>Unregistered</th>
       
     <th >Person Prosecuted <br>(Occupier, Manager etc)</th>

    

     <th >Case No.</th>
      <th >Name <br>of the act.</th>
      <th >Violation.</th>
      <th >Penal <br>Provision</th>
      <th >Name <br>of the Court</th>
      <th >Remarks / Result</th>
    
       
     
     <th >DELETE</th>
    </tr>";  
        $i=0;
    foreach($query_tab_1_c as $squan) {
      $i++;
          
          $monthly_form_id = $squan->monthly_form_id; 
          $row_id = $squan->pros_instituted_id; 
         
           
              
              
      

         $bb=$base_root.$base_path.'admin/monthly-report-ninedel/'.encryption_decryption_fun('encrypt',$monthly_form_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
    
          $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
    
    
    
          $del_preper=l(t('Delete'),$bb ,array('html'=>TRUE)) ;
        
        
        
              if($i%2==0){
            $output1 .= "<tr bgcolor=\"#FCF6CF\">";
         }
        else
        {
        $output1 .= "<tr bgcolor=\"#FEFEF2\">";
        }
      
                $output1.= "<td>".$squan->pros_instituted_name_of_factory."</td>";
                $output1.= "<td>".$squan->pros_instituted_address_of_factory."</td>";
                $output1.= "<td>".$squan->pros_instituted_reg_unreg."</td>";
                $output1.= "<td>".$squan->pros_instituted_person_prosecuted."</td>";
                $output1.= "<td>".$squan->pros_instituted_case_no."</td>";
                $output1.= "<td>".$squan->pros_instituted_name_of_act."</td>";
                $output1.= "<td>".$squan->pros_instituted_violation."</td>";
                $output1.= "<td>".$squan->pros_instituted_penal_provision."</td>";
                $output1.= "<td>".$squan->pros_instituted_name_of_court."</td>";
                $output1.= "<td>".$squan->pros_instituted_remarks_result."</td>";
                $output1.= "<td >".$del_preper."</td>";
               
                
        
       
            
      
              
         $output1 .= "</tr>";
            }
              $output1 .= "</table>";
        
      

  
     }
  }
        $form['step9field']['prpersonlista'] = array(
       '#prefix' => '<div align="left" id="step2_part2_div">'.$output1,
       '#suffix' => '</div>',
       
      );
          
      
        
          
      
       
           
        

           return $form;
         }

         function month_report_step9_submit($form , $form_state) { 


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
  $eightvalue=trim($val['eightvalue']); if(!$eightvalue) $eightvalue= NULL;
  $ninevalue=trim($val['ninevalue']); if(!$ninevalue) $ninevalue= NULL;
  $tenvalue=trim($val['tenvalue']); if(!$tenvalue) $tenvalue= NULL;
  

  $txn = db_transaction();
    try {


      

  
          $maxresult=db_query('select  max(pros_instituted_id) maxsl from labour_factory_statcell_form_5_t9_7_t6'); 
          $result=$maxresult->fetchAssoc();
          $max_sl_number = trim($result['maxsl']); 
          if($max_sl_number==0){$querystring=1; }else{ $querystring=$max_sl_number+1; }
          $rowid=$querystring;

       $fieldsA = array('pros_instituted_id' => $rowid ,'monthly_form_id' => $monthly_form_id, 'form_type'=>'GENERAL','pros_instituted_name_of_factory'=> $onevalue , 'pros_instituted_address_of_factory' =>$twovalue,  'pros_instituted_reg_unreg' =>$threevalue,'pros_instituted_person_prosecuted' =>$fourvalue, 'pros_instituted_case_no' => $fivevalue, 'pros_instituted_name_of_act' => $sixvalue, 'pros_instituted_violation' => $sevenvalue, 'pros_instituted_penal_provision' => $eightvalue, 'pros_instituted_name_of_court' => $ninevalue,'pros_instituted_remarks_result' => $tenvalue);

             db_insert('labour_factory_statcell_form_5_t9_7_t6')->fields($fieldsA)->execute(); 




   

          

               $full_base=$base_root.$base_path.'admin/monthly-report/step9/'.encryption_decryption_fun('encrypt',$monthly_form_id);

             $message = 'DATA  SAVED SUCCESSFULLY  . ';
                      
       
               drupal_set_message(t($message));
             
               drupal_goto($full_base);

              }
  catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/monthly-report/step9/'.encryption_decryption_fun('encrypt',$monthly_form_id);

             $message = 'DATA NOT SAVED   . ';
                      
       
            drupal_set_message(t($message));
             
          drupal_goto($full_base);
  
     }
   }



      function step9_del(  $filenumber = NULL , $rowid = NULL){
    
   global $base_root, $base_path;
    
     $filenumber=  encryption_decryption_fun('decrypt',trim($filenumber));
     
      $rowid=  encryption_decryption_fun('decrypt',trim($rowid));
     // print $filenumber.'ddd'. $rowid;
     // exit;
     
  $txn = db_transaction();
    try {
      
    db_delete('labour_factory_statcell_form_5_t9_7_t6')
    ->condition('monthly_form_id',trim($filenumber))
    ->condition('pros_instituted_id',trim($rowid))
    ->execute();
  
  
  $message = '   delete is successfull ';
  
}
  catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);
  $message = '    row is not  delete ';
     }  
  
     //$aa=$base_root.$base_path.'equalremuins/equalinfringements/'.encryption_decryption_fun('encrypt', trim($filenumber));

      $aa=$base_root.$base_path.'admin/monthly-report/step9/'.encryption_decryption_fun('encrypt',$filenumber);
      drupal_set_message(t($message));
     
      drupal_goto($aa);
      
  }

           ?>