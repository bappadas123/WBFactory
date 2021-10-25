<?php
function month_report_step7( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;

    $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));

    $form['step7field'] = array(
          '#title' => t('<font color="DarkGreen"><b>  7. Orders issued under various Acts & Rules  </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          );

       $form['step7field']['monthlyformid'] = 
         array('#type' => 'hidden',  
         '#value' => $filenumber,
     
        );


     $form['step7field']['one'] = array
              (
           '#prefix' => '<table class="table"><tr><td  style="text-align:center;"  >', 
           '#markup'=>'<b> Name of the Factory  </b>',

              '#suffix'=>'</td>',
     
     
           ); 

              $form['step7field']['two'] = array
              (
           '#prefix' => '<td  style="text-align:center;"   >', 
           '#markup'=>'<b> Address of the Factory  </b>',

              '#suffix'=>'</td>',
     
     
           );


               $form['step7field']['three'] = array
              (
           '#prefix' => '<td  style="text-align:center;"  >', 
           '#markup'=>'<b> Act and S/R under which the order was issued  </b>',

              '#suffix'=>'</td>',
     
     
           );
              $form['step7field']['four'] = array
              (
           '#prefix' => '<td  style="text-align:center;"  >', 
           '#markup'=>'<b> Time allowed  </b>',

              '#suffix'=>'</td>',
     
     
           );
              
         $form['step7field']['five'] = array
              (
           '#prefix' => '<td  style="text-align:center;"  >', 
           '#markup'=>'<b> Brief description including results (attach copies)    </b>',

              '#suffix'=>'</td></tr>',
     
     
           );
            

            

          

            $form['step7field']['onevalue'] = array
              (
           '#prefix' => '<tr> <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
     
     
           );  

            $form['step7field']['twovalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
     
     
           ); 
            $form['step7field']['threevalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
     
     
           );   
    
         $form['step7field']['fourvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
     
     
           ); 

             $form['step7field']['fivevalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td></tr></table>',
     
     
           ); 
            


            

       
        $form['step7field']['submit_button']          = array(
                                 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
                                '#type'         =>'submit',
                                '#value'        =>t(' Add ')
                                );



       $output1='';
      if(trim($filenumber)){
      $query_tab_1_c=db_query('select  *  from labour_factory_statcell_form_5_t7 where  monthly_form_id = :anid', array(':anid' => trim($filenumber) ));
      if($query_tab_1_c->rowCount() > 0) 
              { 
     $output1 = "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > <th >Name of the Factory</th>
      
       <th > Address of the Factory</th>
      <th >Act and S/R under which the order was issued</th>
       
     <th >Time allowed</th>

    

     <th >Brief description including results (attach copies)</th>
    
       
     
     <th >DELETE</th>
    </tr>";  
        $i=0;
    foreach($query_tab_1_c as $squan) {
      $i++;
          
          $monthly_form_id = $squan->monthly_form_id; 
          $row_id = $squan->ord_id; 
           
              
              
      

         $bb=$base_root.$base_path.'admin/monthly-report-sevendel/'.encryption_decryption_fun('encrypt',$monthly_form_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
    
          $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
    
    
    
          $del_preper=l(t('Delete'),$bb ,array('html'=>TRUE)) ;
        
        
        
              if($i%2==0){
            $output1 .= "<tr bgcolor=\"#FCF6CF\">";
         }
        else
        {
        $output1 .= "<tr bgcolor=\"#FEFEF2\">";
        }
      
                $output1.= "<td>".$squan->factory_name."</td>";
                $output1.= "<td>".$squan->factory_address."</td>";
                $output1.= "<td>".$squan->acts_issued."</td>";
                $output1.= "<td>".$squan->time_allowed."</td>";
                $output1.= "<td>".$squan->result_description."</td>";
                $output1.= "<td >".$del_preper."</td>";
               
                
        
       
            
      
              
         $output1 .= "</tr>";
            }
              $output1 .= "</table>";
        
      

  
     }
  }
        $form['step7field']['prpersonlista'] = array(
       '#prefix' => '<div align="left" id="step2_part2_div">'.$output1,
       '#suffix' => '</div>',
       
      );




           return $form;
         }

      function month_report_step7_submit($form , $form_state) { 


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
  

  $txn = db_transaction();
    try {


      

  
          $maxresult=db_query('select  max(ord_id) maxsl from labour_factory_statcell_form_5_t7'); 
          $result=$maxresult->fetchAssoc();
          $max_sl_number = trim($result['maxsl']); 
          if($max_sl_number==0){$querystring=1; }else{ $querystring=$max_sl_number+1; }
          $rowid=$querystring;

       $fieldsA = array('ord_id' => $rowid ,'monthly_form_id' => $monthly_form_id, 'factory_name'=> $onevalue , 'factory_address' =>$twovalue,  'acts_issued' =>$threevalue,'time_allowed' =>$fourvalue, 'result_description' => $fivevalue);

             db_insert('labour_factory_statcell_form_5_t7')->fields($fieldsA)->execute(); 




   

          

               $full_base=$base_root.$base_path.'admin/monthly-report/step7/'.encryption_decryption_fun('encrypt',$monthly_form_id);

             $message = 'DATA  SAVED SUCCESSFULLY  . ';
                      
       
               drupal_set_message(t($message));
             
               drupal_goto($full_base);

              }
  catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/monthly-report/step7/'.encryption_decryption_fun('encrypt',$monthly_form_id);

             $message = 'DATA NOT SAVED   . ';
                      
       
            drupal_set_message(t($message));
             
          drupal_goto($full_base);
  
     }
   }



      function step7_del(  $filenumber = NULL , $rowid = NULL){
    
   global $base_root, $base_path;
    //  $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));
     
      //$tyinfg= encryption_decryption_fun('decrypt', trim($tyinfg));

     $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));
     
      $rowid= encryption_decryption_fun('decrypt', trim($rowid));
     // print $filenumber.'ddd'. $rowid;
     // exit;
     
  $txn = db_transaction();
    try {
      
    db_delete('labour_factory_statcell_form_5_t7')
    ->condition('monthly_form_id',trim($filenumber))
    ->condition('ord_id',trim($rowid))
    ->execute();
  
  
  $message = '   delete is successfull ';
  
}
  catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);
  $message = '    row is not  delete ';
     }  
  
     //$aa=$base_root.$base_path.'equalremuins/equalinfringements/'.encryption_decryption_fun('encrypt', trim($filenumber));

      $aa=$base_root.$base_path.'admin/monthly-report/step7/'.encryption_decryption_fun('encrypt',$filenumber);
      drupal_set_message(t($message));
     
      drupal_goto($aa);
      
  }

           ?>