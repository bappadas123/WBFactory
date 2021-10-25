<?php
function month_report_step13( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;

   $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));

   $get_info_montly_report=get_monthly_area_from_to_date($filenumber);

    $form['step13field'] = array(
          '#title' => t('<font color="DarkGreen">'.$get_info_montly_report.'<b> 13. Application Filled before the Authority under the P.W. Act   </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          );

  $form['step13field']['monthlyformid'] = 
         array('#type' => 'hidden',  
         '#value' => $filenumber,
     
        );
     $form['step13field']['one'] = array
              (
           '#prefix' => '<table class="table" border="1"><tr><td rowspan="2"   >', 
           '#markup'=>'<b> Name of the Factory  </b>',

              '#suffix'=>'</td>',
     
     
           ); 


           $form['step13field']['two'] = array
              (
           '#prefix' => '<td rowspan="2"  >', 
           '#markup'=>'<b> Address of the Factory  </b>',

              '#suffix'=>'</td>',
     
     
           );
             
     $form['step13field']['three'] = array
              (
           '#prefix' => '<td rowspan="2"  >', 
           '#markup'=>'<b> Type of program  </b>',

              '#suffix'=>'</td>',
     
     
           );
             $form['step13field']['four'] = array
              (
           '#prefix' => '<td rowspan="2"  >', 
           '#markup'=>'<b> No. of Persons involved  </b>',

              '#suffix'=>'</td>',
     
     
           );

           $form['step13field']['five'] = array
              (
           '#prefix' => '<td colspan="2" style="text-align:center;"  >', 
           '#markup'=>'<b> Amount of  </b>',

              '#suffix'=>'</td>',
     
     
           );

            $form['step13field']['six'] = array
              (
           '#prefix' => '<td rowspan="2" >', 
           '#markup'=>'<b> Remarks  </b>',

              '#suffix'=>'</td></tr>',
     
     
           );
            $form['step13field']['fiveone'] = array
              (
           '#prefix' => '<tr><td  >', 
           '#markup'=>'<b> Unpaid wages claimed  </b>',

              '#suffix'=>'</td>',
     
     
           );

            $form['step13field']['fivetwo'] = array
              (
           '#prefix' => '<td >', 
           '#markup'=>'<b> Unauthorized deduction claimed </b>',

              '#suffix'=>'</td></tr>',
     
     
           );
            

           $form['step13field']['onevalue'] = array
              (
           '#prefix' => '<tr> <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
     
     
           ); 
           $form['step13field']['twovalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
     
     
           ); 
           $form['step13field']['threevalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
            '#size' => 10,

            '#suffix'=>'</td>',
     
     
           ); 
           $form['step13field']['fourvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
           '#size' => 5,

            '#suffix'=>'</td>',
            '#element_validate' => array('MONTHLY_MANDATORY_INTEGER_CHECKING_validate'),
     
     
           );
           $form['step13field']['fiveonevalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
            '#size' => 5,

            '#suffix'=>'</td>',
            '#element_validate' => array('MONTHLY_MANDATORY_floating_CHECKING_validate'),
     
     
           );
            $form['step13field']['fivetwovalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textfield',
            '#size' => 5,

            '#suffix'=>'</td>',
            '#element_validate' => array('MONTHLY_MANDATORY_floating_CHECKING_validate'),
     
     
           );
            $form['step13field']['sixvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td></tr></table>',
     
     
           ); 
            $form['step13field']['submit_button']          = array(
                                 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
                                '#type'         =>'submit',
                                '#value'        =>t(' Save ')
                                );


          $output1='';
      if(trim($filenumber)){
      $query_tab_1_c=db_query('select  *  from labour_factory_statcell_form_5_t13 where  monthly_form_id = :anid', array(':anid' => trim($filenumber) ));
      if($query_tab_1_c->rowCount() > 0) 
              { 
     $output1 = "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > <th >Name of the Factory</th>
      
       <th > Address of the Factory</th>
      
       
     <th >Type of program</th>

    

     <th >No. of Persons involved</th>
    <th >Unpaid wages claimed</th>
    <th >Unauthorized deduction claimed</th>
    <th >Remarks</th>
    
       
     
     <th >DELETE</th>
    </tr>";  
        $i=0;
    foreach($query_tab_1_c as $squan) {
      $i++;
          
          $monthly_form_id = $squan->monthly_form_id; 
          $row_id = $squan->pw_act_id; 
         
           
              
              
      

         $bb=$base_root.$base_path.'admin/monthly-report-thirteendel/'.encryption_decryption_fun('encrypt',$monthly_form_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
    
          $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
    
    
    
          $del_preper=l(t('Delete'),$bb ,array('html'=>TRUE)) ;
        
        
        
              if($i%2==0){
            $output1 .= "<tr bgcolor=\"#FCF6CF\">";
         }
        else
        {
        $output1 .= "<tr bgcolor=\"#FEFEF2\">";
        }
      
                $output1.= "<td>".$squan->pw_act_name_of_factory."</td>";
                $output1.= "<td>".$squan->pw_act_address_of_factory."</td>";
                $output1.= "<td>".$squan->pw_act_case_no."</td>";
                $output1.= "<td>".$squan->pw_act_persons_involved."</td>";
                $output1.= "<td>".$squan->pw_act_amount_unpaid_wages."</td>";
                $output1.= "<td>".$squan->pw_act_amount_unauthorized_deduction."</td>";
                $output1.= "<td>".$squan->pw_act_remarks."</td>";
                $output1.= "<td >".$del_preper."</td>";
               
                
        
       
            
      
              
         $output1 .= "</tr>";
            }
              $output1 .= "</table>";
        
      

  
     }
  }
        $form['step13field']['prpersonlista'] = array(
       '#prefix' => '<div align="left" id="step2_part2_div">'.$output1,
       '#suffix' => '</div>',
       
      );





           return $form;
         }



    function month_report_step13_submit($form , $form_state) { 


         global $base_root, $base_path,$full_base;




   $val=$form_state['values'];

 
  $monthly_form_id=trim($val['monthlyformid']); 

  //print $monthly_form_id;  
 // exit; 

  $onevalue=trim($val['onevalue']);  if(!$onevalue) $onevalue= NULL;         
  $twovalue=trim($val['twovalue']); if(!$twovalue) $twovalue= NULL;
  $threevalue=trim($val['threevalue']); if(!$threevalue) $threevalue= NULL;
  $fourvalue=trim($val['fourvalue']); if(!$fourvalue) $fourvalue= 0;
  $fiveonevalue=trim($val['fiveonevalue']); if(!$fiveonevalue) $fiveonevalue= 0;
   $fivetwovalue=trim($val['fivetwovalue']); if(!$fivetwovalue) $fivetwovalue= 0;
  $sixvalue=trim($val['sixvalue']); if(!$sixvalue) $sixvalue= NULL;

 
  

  $txn = db_transaction();
    try {


      

  
          $maxresult=db_query('select  max(pw_act_id) maxsl from labour_factory_statcell_form_5_t13'); 
          $result=$maxresult->fetchAssoc();
          $max_sl_number = trim($result['maxsl']); 
          if($max_sl_number==0){$querystring=1; }else{ $querystring=$max_sl_number+1; }
          $rowid=$querystring;

       $fieldsA = array('pw_act_id' => $rowid ,'monthly_form_id' => $monthly_form_id, 'pw_act_name_of_factory'=>$onevalue,'pw_act_address_of_factory'=> $twovalue , 'pw_act_case_no' =>$threevalue,  'pw_act_persons_involved' =>$fourvalue,'pw_act_amount_unpaid_wages' =>$fiveonevalue, 'pw_act_amount_unauthorized_deduction' => $fivetwovalue,  'pw_act_remarks' => $sixvalue);

             db_insert('labour_factory_statcell_form_5_t13')->fields($fieldsA)->execute(); 



   

          

               $full_base=$base_root.$base_path.'admin/monthly-report/step13/'.encryption_decryption_fun('encrypt',$monthly_form_id);

             $message = 'DATA  SAVED SUCCESSFULLY  . ';
                      
       
               drupal_set_message(t($message));
             
               drupal_goto($full_base);

              }
  catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/monthly-report/step13/'.encryption_decryption_fun('encrypt',$monthly_form_id);

             $message = 'DATA NOT SAVED   . ';
                      
       
            drupal_set_message(t($message));
             
          drupal_goto($full_base);
  
     }
   }


   function step13_del(  $filenumber = NULL , $rowid = NULL){
    
      global $base_root, $base_path;
    

     $filenumber=  encryption_decryption_fun('decrypt',trim($filenumber));
     
      $rowid=  encryption_decryption_fun('decrypt',trim($rowid));
     // print $filenumber.'ddd'. $rowid;
     // exit;
     
  $txn = db_transaction();
    try {
      
    db_delete('labour_factory_statcell_form_5_t13')
    ->condition('monthly_form_id',trim($filenumber))
    ->condition('pw_act_id',trim($rowid))
    ->execute();
  
  
  $message = '   delete is successfull ';
  
}
  catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);
  $message = '    row is not  delete ';
     }  
  
     //$aa=$base_root.$base_path.'equalremuins/equalinfringements/'.encryption_decryption_fun('encrypt', trim($filenumber));

      $aa=$base_root.$base_path.'admin/monthly-report/step13/'.encryption_decryption_fun('encrypt',$filenumber);
      drupal_set_message(t($message));
     
      drupal_goto($aa);
      
  }
           ?>