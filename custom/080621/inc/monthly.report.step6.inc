<?php
function month_report_step6( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;
   
    $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));

    $form['step6field'] = array(
          '#title' => t('<font color="DarkGreen"><b>   Chemical Factories  </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          );

      $form['step6field']['monthlyformid'] = 
      array('#type' => 'hidden',  
      '#value' => $filenumber,
     
     );


     $form['step6field']['one'] = array
              (
           '#prefix' => '<table class="table"><tr><td  style="text-align:center;" rowspan="2" >', 
           '#markup'=>'<b> Name of the Factory  </b>',

              '#suffix'=>'</td>',
     
     
           ); 

              $form['step6field']['two'] = array
              (
           '#prefix' => '<td  style="text-align:center;" rowspan="2"  >', 
           '#markup'=>'<b> Address of the Factory  </b>',

              '#suffix'=>'</td>',
     
     
           );


               $form['step6field']['three'] = array
              (
           '#prefix' => '<td  style="text-align:center;" colspan="2" >', 
           '#markup'=>'<b> Raw Materials Used  </b>',

              '#suffix'=>'</td>',
     
     
           );
              $form['step6field']['four'] = array
              (
           '#prefix' => '<td  style="text-align:center;" colspan="2" >', 
           '#markup'=>'<b> Intermediaries  </b>',

              '#suffix'=>'</td>',
     
     
           );
              
         $form['step6field']['five'] = array
              (
           '#prefix' => '<td  style="text-align:center;" colspan="2" >', 
           '#markup'=>'<b> Products Manufactured  </b>',

              '#suffix'=>'</td>',
     
     
           );
            $form['step6field']['six'] = array
              (
           '#prefix' => '<td  style="text-align:center;" rowspan="2" >', 
           '#markup'=>'<b> Possible Hazards  </b>',

              '#suffix'=>'</td>',
     
     
           ); 
              $form['step6field']['seven'] = array
              (
           '#prefix' => '<td  style="text-align:center;" rowspan="2" >', 
           '#markup'=>'<b> Action Taken / Remarks  </b>',

              '#suffix'=>'</td></tr>',
     
     
           );

           $form['step6field']['threeone'] = array
              (
           '#prefix' => '<tr><td  style="text-align:center;"  >', 
           '#markup'=>'<b> Name  </b>',

              '#suffix'=>'</td>',
     
     
           ); 
            $form['step6field']['threetwo'] = array
              (
           '#prefix' => '<td  style="text-align:center;"  >', 
           '#markup'=>'<b> Max. Qty. Stored  </b>',

              '#suffix'=>'</td>',
     
     
           );  


           $form['step6field']['fourone'] = array
              (
           '#prefix' => '<td  style="text-align:center;"  >', 
           '#markup'=>'<b> Name  </b>',

              '#suffix'=>'</td>',
     
     
           ); 
            $form['step6field']['fourtwo'] = array
              (
           '#prefix' => '<td  style="text-align:center;"  >', 
           '#markup'=>'<b> Max. Qty. Stored  </b>',

              '#suffix'=>'</td>',
     
     
           );  

            $form['step6field']['fiveone'] = array
              (
           '#prefix' => '<td  style="text-align:center;"  >', 
           '#markup'=>'<b> Name  </b>',

              '#suffix'=>'</td>',
     
     
           ); 
            $form['step6field']['fivetwo'] = array
              (
           '#prefix' => '<td  style="text-align:center;"  >', 
           '#markup'=>'<b> Max. Qty. Stored  </b>',

              '#suffix'=>'</td></tr>',
     
     
           ); 

            $form['step6field']['onevalue'] = array
              (
           '#prefix' => '<tr> <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
     
     
           );  

            $form['step6field']['twovalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
     
     
           ); 
            $form['step6field']['threevalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
     
     
           );   
    
         $form['step6field']['fourvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
     
     
           ); 

             $form['step6field']['fivevalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
     
     
           ); 
            $form['step6field']['sixvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
     
     
           );  


            $form['step6field']['sevenvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
     
     
           ); 

           $form['step6field']['eightvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
     
     
           );   

        $form['step6field']['ninevalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
     
     
           );
            $form['step6field']['tenvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td></tr></table>',
     
     
           );    

        $form['step6field']['submit_button']          = array(
                                 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
                                '#type'         =>'submit',
                                '#value'        =>t(' Add ')
                                );



      $output1='';
      if(trim($filenumber)){
      $query_tab_1_c=db_query('select  *  from labour_factory_statcell_form_5_t6_6_t3 where  monthly_form_id = :anid', array(':anid' => trim($filenumber) ));
      if($query_tab_1_c->rowCount() > 0) 
              { 
     $output1 = "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > <th >Name of the Factory</th>
      
       <th > Address of the Factory</th>
      <th >Name</th>
       
     <th >Max. Qty. Stored</th>

    

     <th >Name</th>
     <th >Max. Qty. Stored</th>
       
      <th >Name</th>
      <th >Max. Qty. Stored</th>

       <th >Possible Hazards</th>
      <th >Action Taken / Remarks</th>
       
     
     <th >DELETE</th>
    </tr>";  
        $i=0;
    foreach($query_tab_1_c as $squan) {
      $i++;
          
          $monthly_form_id = $squan->monthly_form_id; 
          $row_id = $squan->chem_fac_id; 
           
              
              
      

         $bb=$base_root.$base_path.'admin/monthly-report-sixdel/'.encryption_decryption_fun('encrypt',$monthly_form_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
    
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
                $output1.= "<td>".$squan->chem_fac_name_of_factory."</td>";
                $output1.= "<td>".$squan->chem_fac_address_of_factory."</td>";
                $output1.= "<td>".$squan->chem_fac_raw_mat_name."</td>";
                $output1.= "<td>".$squan->chem_fac_raw_mat_quantity."</td>";
                
             
                $output1.= "<td>".$squan->chem_fac_intermediaries_name."</td>";
                $output1.= "<td>".$squan->chem_fac_intermediaries_quantity."</td>";

                $output1.= "<td>".$squan->chem_fac_products_name."</td>";
                $output1.= "<td>".$squan->chem_fac_products_quantity."</td>";

                $output1.= "<td>".$squan->chem_fac_possible_hazards."</td>";
                $output1.= "<td>".$squan->chem_fac_action_remarks."</td>";
        
       
        $output1.= "<td >".$del_preper."</td>";
      
              
         $output1 .= "</tr>";
            }
              $output1 .= "</table>";
        
      

  
     }
  }
   $form['step6field']['prpersonlista'] = array(
    '#prefix' => '<div align="left" id="step2_part2_div">'.$output1,
    '#suffix' => '</div>',
       
  );




           return $form;
         }

  function month_report_step6_submit($form , $form_state) { 


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
  $eightvalue=trim($val['eightvalue']); if(!$eightvalue) $eightvalue= NULL;
  $ninevalue=trim($val['ninevalue']); if(!$ninevalue) $ninevalue= NULL;
  $tenvalue=trim($val['tenvalue']); if(!$tenvalue) $tenvalue= NULL;


  $txn = db_transaction();
    try {


      

  
          $maxresult=db_query('select  max(chem_fac_id) maxsl from labour_factory_statcell_form_5_t6_6_t3'); 
          $result=$maxresult->fetchAssoc();
          $max_sl_number = trim($result['maxsl']); 
         if($max_sl_number==0){$querystring=1; }else{ $querystring=$max_sl_number+1; }
          $rowid=$querystring;

       $fieldsA = array('chem_fac_id' => $rowid ,'monthly_form_id' => $monthly_form_id, 'form_type'=> 'GENERAL' , 'chem_fac_name_of_factory' =>$onevalue,  'chem_fac_address_of_factory' =>$twovalue,'chem_fac_raw_mat_name' =>$threevalue, 'chem_fac_raw_mat_quantity' => $fourvalue, 'chem_fac_intermediaries_name' => $fivevalue, 'chem_fac_intermediaries_quantity' => $sixvalue, 'chem_fac_products_name' => $sevenvalue, 'chem_fac_products_quantity' => $eightvalue, 'chem_fac_possible_hazards' => $ninevalue, 'chem_fac_action_remarks' => $tenvalue);

             db_insert('labour_factory_statcell_form_5_t6_6_t3')->fields($fieldsA)->execute(); 




   

          

               $full_base=$base_root.$base_path.'admin/monthly-report/step6/'.encryption_decryption_fun('encrypt',$monthly_form_id);

             $message = 'DATA  SAVED SUCCESSFULLY  . ';
                      
       
               drupal_set_message(t($message));
             
               drupal_goto($full_base);

              }
  catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/monthly-report/step6/'.encryption_decryption_fun('encrypt',$monthly_form_id);

             $message = 'DATA NOT SAVED   . ';
                      
       
            drupal_set_message(t($message));
             
          drupal_goto($full_base);
  
     }
   }


   function step6_del(  $filenumber = NULL , $rowid = NULL){
    
   global $base_root, $base_path;
    

     $filenumber=  encryption_decryption_fun('decrypt',trim($filenumber));
     
      $rowid=  encryption_decryption_fun('decrypt',trim($rowid));
     // print $filenumber.'ddd'. $rowid;
     // exit;
     
  $txn = db_transaction();
    try {
      
    db_delete('labour_factory_statcell_form_5_t6_6_t3')
    ->condition('monthly_form_id',trim($filenumber))
    ->condition('chem_fac_id',trim($rowid))
    ->execute();
  
  
  $message = '   delete is successfull ';
  
}
  catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);
  $message = '    row is not  delete ';
     }  
  
     //$aa=$base_root.$base_path.'equalremuins/equalinfringements/'.encryption_decryption_fun('encrypt', trim($filenumber));

      $aa=$base_root.$base_path.'admin/monthly-report/step6/'.encryption_decryption_fun('encrypt',$filenumber);
      drupal_set_message(t($message));
     
      drupal_goto($aa);
      
  }

           ?>