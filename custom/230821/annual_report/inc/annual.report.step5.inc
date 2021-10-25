<?php

function annual_report_step5( $form, &$form_state, $filenumber= NULL   ){


	    $filenumber=encryption_decryption_fun('decrypt',$filenumber);
	
	
	 global $base_root, $base_path , $user;
	 
	   $mr_istquery = db_select('labour_factory_statcell_annual_report', 'a');
       
        $mr_istquery->condition('a.annual_inspection_id',trim($filenumber),'=');
      
    
        $mr_istquery->fields('a',array('area','inspector_id', 'report_from_date','report_to_date'));
        $mr_istquery_result = $mr_istquery->execute(); 
    
       $result_mrist=$mr_istquery_result->fetchAssoc();
       $area=$result_mrist['area'];
       $inspector_id=$result_mrist['inspector_id'];
       $inspector_name=get_name($inspector_id);
       $report_from_date=date('d-m-Y', strtotime($result_mrist['report_from_date']));
       $report_to_date=date('d-m-Y', strtotime($result_mrist['report_to_date']));
	 
	 $form['step5field'] = array(
          '#title' => t('<b>Area:'.$area.' , From date: '.$report_from_date.' , To date: '.$report_to_date.'</b>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 


       $form['step5field']['inspectionid'] = 
	    array('#type' => 'hidden',  
	    '#value' => $filenumber,
	   
	   );     

		
        $step6_select_query = db_select('labour_factory_statcell_annual_report_t5_a', 'a');
       
        $step6_select_query->condition('a.annual_inspection_id',trim($filenumber),'=');
      
		
        $step6_select_query->fields('a',array('factory_providing_ambulance','factory_providing_canteen','factory_providing_creche','factory_not_providing_ambulance','factory_not_providing_canteen','factory_not_providing_creche','factory_providing_1st_canteen','factory_providing_rest_shelter_lunch', 'factory_not_providing_rest_shelter_lunch','factory_providing_1st_rest_shelter_lunch','factory_providing_1st_ambulance_creche'));
        $step6_select_query_result = $step6_select_query->execute(); 
		
		$result_step6_A=$step6_select_query_result->fetchAssoc();
		$factory_providing_ambulance=$result_step6_A['factory_providing_ambulance'];
        $factory_providing_canteen=$result_step6_A['factory_providing_canteen'];
        $factory_providing_creche=$result_step6_A['factory_providing_creche'];
        $factory_providing_rest_shelter_lunch=$result_step6_A['factory_providing_rest_shelter_lunch'];
		
		$factory_not_providing_ambulance=$result_step6_A['factory_not_providing_ambulance'];
		$factory_not_providing_canteen=$result_step6_A['factory_not_providing_canteen'];
		$factory_not_providing_creche=$result_step6_A['factory_not_providing_creche'];
		$factory_not_providing_rest_shelter_lunch=$result_step6_A['factory_not_providing_rest_shelter_lunch'];

		$factory_providing_1st_canteen=$result_step6_A['factory_providing_1st_canteen'];
		$factory_providing_1st_rest_shelter_lunch=$result_step6_A['factory_providing_1st_rest_shelter_lunch'];
        $factory_providing_1st_ambulance_creche=$result_step6_A['factory_providing_1st_ambulance_creche'];



        $step6_select_B_query = db_select('labour_factory_statcell_annual_report_t5_b', 'b');
       
        $step6_select_B_query->condition('b.annual_inspection_id',trim($filenumber),'=');
      
		
        $step6_select_B_query->fields('b',array('ambulance' ,'whole_time' ,'part_time' ,
  'consultant' ,
  'hygiene_lab' ,
  'hygienist' ,
  'health_supervisor' ,
  'blood_examined' ,
  'urine_examined' ,
  'stool_examined' ,
  'radiology_xray' ,
  'lung_function_examined' ,
  'sputum_examined' ,
  'liver_function_examined' ,
  'audiometry_examined' ,
  'occupational_examined' ,
  'fitness_examined' ,
  'others_examined'));
        $step6_result_B = $step6_select_B_query->execute(); 
		
		$result_B=$step6_result_B->fetchAssoc();
		$ambulance=$result_B['ambulance'];
        $whole_time=$result_B['whole_time'];
        $part_time=$result_B['part_time'];
        $consultant=$result_B['consultant'];
		
		$hygiene_lab=$result_B['hygiene_lab'];
		$hygienist=$result_B['hygienist'];
		$health_supervisor=$result_B['health_supervisor'];

		
        $blood_examined=$result_B['blood_examined'];
		$urine_examined=$result_B['urine_examined'];
		$stool_examined=$result_B['stool_examined'];
        $radiology_xray=$result_B['radiology_xray'];


        $lung_function_examined=$result_B['lung_function_examined'];
		$sputum_examined=$result_B['sputum_examined'];
		$liver_function_examined=$result_B['liver_function_examined'];
        $audiometry_examined=$result_B['audiometry_examined'];

        $occupational_examined=$result_B['occupational_examined'];
        $fitness_examined=$result_B['fitness_examined'];
        $others_examined=$result_B['others_examined'];
		


     	
$form['step5field']['colD1'] = array
              (
		       '#prefix' => '<div class="table-panel-header"><b>5.A. Welfare facilities</b> </div>
			   <div class="table-responsive">
			   <table class="table table-striped table-bordered table-responsive admin-custom-table">
			   <thead>
			   <tr><th colspan="4" >', 
		       '#markup'=>'<b> No. of factories providing  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );


                $form['step5field']['colD2'] = array
              (
		       '#prefix' => ' <th colspan="4"  >', 
		        '#markup'=>'<b> No. of factories not providing  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step5field']['colD3'] = array
              (
		       '#prefix' => ' <th colspan="3"  >', 
		        '#markup'=>'<b> No. of factories providing for the first time during the year  </b>',
           

		        '#suffix'=>'</th></tr></thead>',
	   
	   
           ); 


               $form['step5field']['colD11'] = array
              (
		       '#prefix' => '<tr> <td   >', 
		        '#markup'=>'<b> Ambulance Room </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


            $form['step5field']['colD12'] = array
              (
		       '#prefix' => ' <td   >', 
		        '#markup'=>'<b> Canteen </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

              $form['step5field']['colD13'] = array
              (
		       '#prefix' => ' <td   >', 
		        '#markup'=>'<b> Rest Room/Shelter/Lunch Room </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           );   

           $form['step5field']['colD14'] = array
              (
		       '#prefix' => ' <td>', 
		        '#markup'=>'<b> Creche </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           );  

            $form['step5field']['colD21'] = array
              (
		       '#prefix' => ' <td>', 
		        '#markup'=>'<b> Ambulance Room </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

           $form['step5field']['colD22'] = array
              (
		       '#prefix' => ' <td>', 
		        '#markup'=>'<b> Canteen </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           );   

           $form['step5field']['colD23'] = array
              (
		       '#prefix' => ' <td>', 
		        '#markup'=>'<b> Rest Room/Shelter/Lunch Room </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           );  

           $form['step5field']['colD24'] = array
              (
		       '#prefix' => ' <td>', 
		        '#markup'=>'<b> Creche </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           );  


           $form['step5field']['colD31'] = array
              (
		       '#prefix' => ' <td>', 
		        '#markup'=>'<b> Ambulance Room/Creche </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           );  
    $form['step5field']['colD32'] = array
              (
		       '#prefix' => ' <td>', 
		        '#markup'=>'<b> Canteen </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           );  

           $form['step5field']['colD33'] = array
              (
		       '#prefix' => ' <td>', 
		        '#markup'=>'<b> Rest Room/Shelter/Lunch Room </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

       

              $form['step5field']['col11val'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		         '#default_value' =>$factory_providing_ambulance
	   
	   
           );

              

              
              
             

         $form['step5field']['col12val'] = array
              (
		       '#prefix' => ' <td  >', 
		    
		       '#type' => 'textfield',
               '#size' => 5,
		       '#suffix'=>'</td>',
		        '#default_value' =>$factory_providing_canteen
	   
	   
           );

             $form['step5field']['col13val'] = array
              (
		       '#prefix' => ' <td  >', 
		    
		       '#type' => 'textfield',
               '#size' => 5,
		       '#suffix'=>'</td>',
	           '#default_value' =>$factory_providing_creche
	   
           );

 $form['step5field']['col14val'] = array
              (
		       '#prefix' => ' <td  >', 
		    
		       '#type' => 'textfield',
               '#size' => 5,
		       '#suffix'=>'</td>',
	          '#default_value' =>$factory_providing_rest_shelter_lunch
	   
           );


            $form['step5field']['col21val'] = array
              (
		       '#prefix' => ' <td  >', 
		    
		       '#type' => 'textfield',
               '#size' => 5,
		       '#suffix'=>'</td>',
		        '#default_value' =>$factory_not_providing_ambulance
	   
	   
           );

            $form['step5field']['col22val'] = array
              (
		       '#prefix' => ' <td  >', 
		    
		       '#type' => 'textfield',
               '#size' => 5,
		       '#suffix'=>'</td>',
	          '#default_value' =>$factory_not_providing_canteen
	   
           );

           $form['step5field']['col23val'] = array
              (
		       '#prefix' => ' <td  >', 
		    
		       '#type' => 'textfield',
               '#size' => 5,
		       '#suffix'=>'</td>',
	         '#default_value' =>$factory_not_providing_creche
	   
           );

           $form['step5field']['col24val'] = array
              (
		       '#prefix' => ' <td  >', 
		    
		       '#type' => 'textfield',
               '#size' => 5,
		       '#suffix'=>'</td>',
	           '#default_value' =>$factory_not_providing_rest_shelter_lunch
	   
           );

           $form['step5field']['col31val'] = array
              (
		       '#prefix' => ' <td  >', 
		    
		       '#type' => 'textfield',
               '#size' => 5,
		       '#suffix'=>'</td>',
	          '#default_value' =>$factory_providing_1st_ambulance_creche
	   
           );

            $form['step5field']['col32val'] = array
              (
		       '#prefix' => ' <td  >', 
		    
		       '#type' => 'textfield',
               '#size' => 5,
		       '#suffix'=>'</td>',
	   
	          '#default_value' =>$factory_providing_1st_canteen,
           );

            $form['step5field']['col33val'] = array
              (
		       '#prefix' => ' <td  >', 
		    
		       '#type' => 'textfield',
               '#size' => 5,
                 '#default_value' =>$factory_providing_1st_rest_shelter_lunch,
		       '#suffix'=>'</td></tr></table></div>',
	   
	   
           );




         
                $form['step5Bfield'] = array(
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 

		$form['step5Bfield']['fiveBhead'] = array
              (
		       //'#prefix' => '<div>', 
		       //'#markup'=>'',

		         // '#suffix'=>'</div>',
	   
	   
           );
     	
$form['step5Bfield']['colB1'] = array
              (
		       '#prefix' => '<div class="table-panel-header"><b>  5.B. Additional health and Welfare facilities  </b></div><div class="table-responsive"><table class="table table-striped table-bordered table-responsive">
			   <thead><tr><th colspan="7">No of factories providing</th></tr></thead>
			   <tr><td rowspan="2" >', 
		       '#markup'=>'<b> Ambulance  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );


                $form['step5Bfield']['colB2'] = array
              (
		       '#prefix' => ' <td colspan="3"  >', 
		        '#markup'=>'<b> Qualified Medical Practitioners  </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


               $form['step5Bfield']['colB3'] = array
              (
		       '#prefix' => ' <td rowspan="2"  >', 
		        '#markup'=>'<b> Industrial hygiene laboratory  </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


               $form['step5Bfield']['colB4'] = array
              (
		       '#prefix' => ' <td rowspan="2"  >', 
		        '#markup'=>'<b> Industrial laboratory </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


            $form['step5Bfield']['colB5'] = array
              (
		       '#prefix' => ' <td  rowspan="2" >', 
		        '#markup'=>'<b> Industrial health supervisor </b>',
           

		        '#suffix'=>'</td></tr>',
	   
	   
           ); 

              $form['step5Bfield']['colB21'] = array
              (
		       '#prefix' => '<tr> <td   >', 
		        '#markup'=>'<b> Whole time </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           );   

           $form['step5Bfield']['colB22'] = array
              (
		       '#prefix' => ' <td>', 
		        '#markup'=>'<b> Part time </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           );  

            $form['step5Bfield']['colB23'] = array
              (
		       '#prefix' => ' <td>', 
		        '#markup'=>'<b> Consultant (Specialist) </b>',
           

		        '#suffix'=>'</td></tr>',
	   
	   
           ); 

           
                
       
        
              $form['step5Bfield']['colAAval'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		          '#default_value' =>$ambulance,
	   
	   
           );  


             $form['step5Bfield']['colBBval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	            '#default_value' =>$whole_time,
	   
           );  

    $form['step5Bfield']['colCCval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	           '#default_value' =>$part_time,
	   
           ); 


            $form['step5Bfield']['colDDval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	          '#default_value' =>$consultant,
	   
           ); 
              
    $form['step5Bfield']['colEEval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	        '#default_value' =>$hygiene_lab,
	   
           ); 
              
              
             

         $form['step5Bfield']['colFFval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		         '#default_value' =>$hygienist,
	   
	   
           ); 

            $form['step5Bfield']['colGGval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td></tr></table></div>',
		         '#default_value' =>$health_supervisor,
	   
	   
           ); 


            

              $form['step5Cfield'] = array(
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 

           
             $form['step5Cfield']['colC1'] = array
              (
		       '#prefix' => '<div class="table-panel-header"><b> 5.C. Clinical and laboratory examinations of workers during the year</b> </div>
			   <div class="table-responsive">
			   <table class="table table-striped table-bordered table-responsive">
			   <thead><tr><th >', 
		       '#markup'=>'<b> Nature of Laboratory examinations </b>',

		          '#suffix'=>'</th>',
	   
	   
           );


          $form['step5Cfield']['colC1val'] = array
              (
		       '#prefix' => ' <th  >', 
		        '#markup'=>'<b> No. of workers examined </b>',

		        '#suffix'=>'</th></tr></thead>',
	   
	   
           ); 

          $form['step5Cfield']['colC2'] = array
              (
		       '#prefix' => '<tr> <td colspan="2"  >', 
		        '#markup'=>'<b> 1.Pathological </b>',

		        '#suffix'=>'</td></tr>',
	   
	   
           ); 


               $form['step5Cfield']['colC3'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		        '#markup'=>'<b> (i) Blood  </b>',

		        '#suffix'=>'</td>',
	   
	   
           ); 

        $form['step5Cfield']['colC3val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
               // '#size' => 5,
            
		        '#suffix'=>'</td></tr>',
		         '#default_value' =>$blood_examined,
	   
	   
           ); 
          
                  
		
        
		
     


       

             $form['step5Cfield']['colC4'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		        '#markup'=>'<b> (ii) Urine  </b>',

		        '#suffix'=>'</td>',
	   
	   
           ); 

        $form['step5Cfield']['colC4val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
               // '#size' => 5,
            
		        '#suffix'=>'</td></tr>',
		        '#default_value' =>$urine_examined,
	   
	   
           );

                $form['step5Cfield']['colC5'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		        '#markup'=>'<b> (iii) Stool - </b>',

		        '#suffix'=>'</td>',
	   
	   
           ); 

        $form['step5Cfield']['colC5val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
               // '#size' => 5,
            
		        '#suffix'=>'</td></tr>',
		          '#default_value' =>$stool_examined,
	   
	   
           ); 

                $form['step5Cfield']['colC6'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		        '#markup'=>'<b> 2. Radiological (X-Ray) - </b>',

		        '#suffix'=>'</td>',
	   
	   
           ); 

        $form['step5Cfield']['colC6val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
               // '#size' => 5,
            
		        '#suffix'=>'</td></tr>',
	           '#default_value' =>$radiology_xray,
	   
           ); 

               $form['step5Cfield']['colC7'] = array
              (
		       '#prefix' => '<tr> <td colspan="2"  >', 
		        '#markup'=>'<b> 3. Physiological : </b>',

		        '#suffix'=>'</td></tr>',
	   
	   
           ); 

               $form['step5Cfield']['colC8'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		        '#markup'=>'<b> (i) Lung Function test - </b>',

		        '#suffix'=>'</td>',
	   
	   
           ); 

        $form['step5Cfield']['colC8val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
               // '#size' => 5,
            
		        '#suffix'=>'</td></tr>',
		           '#default_value' =>$lung_function_examined,
	   
	   
           ); 

              $form['step5Cfield']['colC9'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		        '#markup'=>'<b> (ii) Sputum test - </b>',

		        '#suffix'=>'</td>',
	   
	   
           ); 

        $form['step5Cfield']['colC9val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
               // '#size' => 5,
            
		        '#suffix'=>'</td></tr>',
		         '#default_value' =>$sputum_examined,
	   
	   
           ); 

                $form['step5Cfield']['colC10'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		        '#markup'=>'<b> (iii) Liver function test - </b>',

		        '#suffix'=>'</td>',
	   
	   
           ); 

        $form['step5Cfield']['colC10val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
               // '#size' => 5,
            
		        '#suffix'=>'</td></tr>',
		          '#default_value' =>$liver_function_examined,
	   
	   
           ); 

              $form['step5Cfield']['colC11'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		        '#markup'=>'<b> (iv) Audiometry - </b>',

		        '#suffix'=>'</td>',
	   
	   
           ); 

        $form['step5Cfield']['colC11val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
               // '#size' => 5,
            
		        '#suffix'=>'</td></tr>',
		          '#default_value' =>$audiometry_examined,
	   
	   
	   
           ); 

                 $form['step5Cfield']['colC12'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		        '#markup'=>'<b> (v) Occupational diseases suspected  - </b>',

		        '#suffix'=>'</td>',
	   
	   
           ); 

        $form['step5Cfield']['colC12val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
               // '#size' => 5,
            
		        '#suffix'=>'</td></tr>',
		           '#default_value' =>$occupational_examined,
	   
	   
           ); 


                 $form['step5Cfield']['colC13'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		        '#markup'=>'<b> (vi) No. of workers declared unfit for further work  - </b>',

		        '#suffix'=>'</td>',
	   
	   
           ); 

        $form['step5Cfield']['colC13val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
               // '#size' => 5,
            
		        '#suffix'=>'</td></tr>',
		          '#default_value' =>$fitness_examined,
	   
	   
           ); 

                $form['step5Cfield']['colC14'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		        '#markup'=>'<b> (vii)Others  - </b>',

		        '#suffix'=>'</td>',
	   
	   
           ); 

        $form['step5Cfield']['colC14val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
               // '#size' => 5,
            
		        '#suffix'=>'</td></tr></table></div>',
		          '#default_value' =>$others_examined,
	   
	   
           ); 




            


			
		 
		 
	
	 	
		
		
 
             



		
				
	$form['submit_button']					= array(
																 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
																'#type'					=>'submit',
																'#value'				=>t(' Save ')
																);
														
														  
	        return $form; 
  }






function annual_report_step5_submit($form , $form_state) {	

                global $base_root, $base_path,$full_base;




$val=$form_state['values'];
//print_r($val);
//exit;


    $inspectionid=trim($val['inspectionid']);
    //part A
	$col11val=trim($val['col11val']); if(!$col11val)  $col11val= NULL;   
	$col12val=trim($val['col12val']); if(!$col12val)  $col12val= NULL;   
	$col13val=trim($val['col13val']); if(!$col13val) $col13val= NULL;   
	$col14val=trim($val['col14val']); if(!$col14val) $col14val= NULL;   

	$col21val=trim($val['col21val']); if(!$col21val) $col21val= NULL;   
	$col22val=trim($val['col22val']); if(!$col22val) $col22val= NULL;   
	$col23val=trim($val['col23val']); if(!$col23val) $col23val= NULL;   
	$col24val=trim($val['col24val']); if(!$col24val) $col24val= NULL;   

	$col31val=trim($val['col31val']); if(!$col31val) $col31val= NULL;   
    $col32val=trim($val['col32val']); if(!$col32val) $col32val= NULL;   
    $col33val=trim($val['col33val']); if(!$col33val) $col33val= NULL;   


    //part B

    $colAAval=trim($val['colAAval']); if(!$colAAval) $colAAval= NULL;   
    $colBBval=trim($val['colBBval']); if(!$colBBval) $colBBval= NULL;   
    $colCCval=trim($val['colCCval']); if(!$colCCval) $colCCval= NULL; 
    $colDDval=trim($val['colDDval']); if(!$colDDval) $colDDval= NULL; 
    $colEEval=trim($val['colEEval']); if(!$colEEval) $colEEval= NULL;
    $colFFval=trim($val['colFFval']); if(!$colFFval) $colFFval= NULL;        
    $colGGval=trim($val['colGGval']); if(!$colGGval) $colGGval= NULL; 



    $colC3val=trim($val['colC3val']); if(!$colC3val) $colC3val= NULL;   
    $colC4val=trim($val['colC4val']); if(!$colC4val) $colC4val= NULL;   
    $colC5val=trim($val['colC5val']); if(!$colC5val) $colC5val= NULL; 
    $colC6val=trim($val['colC6val']); if(!$colC6val) $colC6val= NULL; 
    $colC8val=trim($val['colC8val']); if(!$colC8val) $colC8val= NULL;
    $colC9val=trim($val['colC9val']); if(!$colC9val) $colC9val= NULL;        
    $colC10val=trim($val['colC10val']); if(!$colC10val) $colC10val= NULL; 
    $colC11val=trim($val['colC11val']); if(!$colC11val) $colC11val= NULL;
    $colC12val=trim($val['colC12val']); if(!$colC12val) $colC12val= NULL; 
    $colC13val=trim($val['colC13val']); if(!$colC13val) $colC13val= NULL; 
    $colC14val=trim($val['colC14val']); if(!$colC14val) $colC14val= NULL; 






	

 $txn = db_transaction();
	  try {
            $maxresult=db_query('select  max(row_id) maxsl from labour_factory_statcell_annual_report_t5_a');	
	        $result=$maxresult->fetchAssoc();
	        $max_sl_number = trim($result['maxsl']); 
            if($max_sl_number==0){$querystring=1;	}else{ $querystring=$max_sl_number+1; }
		    $autoGENNO=$querystring;
	     
		    

	       
	        
	                     
      

      $query_update_5a_yes=db_query('select  * from labour_factory_statcell_annual_report_t5_a where  annual_inspection_id = :filenumber', array(':filenumber' => $inspectionid));

        //print 'aaa'.$inspectionid.''.$query_update_5a_yes->rowCount();
        //exit;

       if($query_update_5a_yes->rowCount() > 0 ) 
          {
         $query_update_5A = db_update('labour_factory_statcell_annual_report_t5_a');
         $query_update_5A->fields(array(
		   'factory_providing_ambulance' =>$col11val, 'factory_providing_canteen' => $col12val, 'factory_providing_creche' => $col13val, 'factory_not_providing_ambulance' => $col21val, 'factory_not_providing_canteen' => $col22val, 'factory_not_providing_creche' => $col23val, 'factory_providing_1st_canteen' => $col32val
                         , 'factory_providing_rest_shelter_lunch' => $col14val, 'factory_not_providing_rest_shelter_lunch' => $col24val, 'factory_providing_1st_rest_shelter_lunch' => $col33val, 'factory_providing_1st_ambulance_creche' => $col31val ));
										
										
										
       $query_update_5A->condition('annual_inspection_id',$inspectionid);
       $query_update_5A->execute();


        $query_update_5B = db_update('labour_factory_statcell_annual_report_t5_b');
        $query_update_5B->fields(array(
		   'ambulance' =>$colAAval, 'whole_time' => $colBBval, 'part_time' => $colCCval, 'consultant' => $colDDval, 'hygiene_lab' => $colEEval, 'hygienist' => $colFFval, 'health_supervisor' => $colGGval
                         , 'blood_examined' => $colC3val, 'urine_examined' => $colC4val, 'stool_examined' => $colC5val, 'radiology_xray' => $colC6val

                         , 'lung_function_examined' => $colC8val , 'sputum_examined' => $colC9val , 'liver_function_examined' => $colC10val , 'audiometry_examined' => $colC11val

                         , 'occupational_examined' => $colC12val, 'fitness_examined' => $colC13val, 'others_examined' => $colC14val ));
										
										
										
       $query_update_5B->condition('annual_inspection_id',$inspectionid);
       $query_update_5B->execute();

	              }               
		  
                 else
                 {


                         $fieldsE = array('row_id' => $autoGENNO, 'annual_inspection_id' =>$inspectionid,'factory_providing_ambulance' =>$col11val, 'factory_providing_canteen' => $col12val, 'factory_providing_creche' => $col13val, 'factory_not_providing_ambulance' => $col21val, 'factory_not_providing_canteen' => $col22val, 'factory_not_providing_creche' => $col23val, 'factory_providing_1st_canteen' => $col32val
                         , 'factory_providing_rest_shelter_lunch' => $col14val, 'factory_not_providing_rest_shelter_lunch' => $col24val, 'factory_providing_1st_rest_shelter_lunch' => $col33val, 'factory_providing_1st_ambulance_creche' => $col31val);
		  
		   
                      db_insert('labour_factory_statcell_annual_report_t5_a')->fields($fieldsE)->execute();	





                       $fieldsE = array('row_id' => $autoGENNO, 'annual_inspection_id' =>$inspectionid,'ambulance' =>$colAAval, 'whole_time' => $colBBval, 'part_time' => $colCCval, 'consultant' => $colDDval, 'hygiene_lab' => $colEEval, 'hygienist' => $colFFval, 'health_supervisor' => $colGGval
                         , 'blood_examined' => $colC3val, 'urine_examined' => $colC4val, 'stool_examined' => $colC5val, 'radiology_xray' => $colC6val

                         , 'lung_function_examined' => $colC8val , 'sputum_examined' => $colC9val , 'liver_function_examined' => $colC10val , 'audiometry_examined' => $colC11val

                         , 'occupational_examined' => $colC12val, 'fitness_examined' => $colC13val, 'others_examined' => $colC14val);
		  
		   
                      db_insert('labour_factory_statcell_annual_report_t5_b')->fields($fieldsE)->execute();	
	 
	                 }
	                   $message = 'DATA  SAVED  SUCCESSFULLY  . ';
                      
				 
	           
	              drupal_set_message(t($message));
				       //$full_base=$base_root.$base_path.'admin/annual-report/'.encryption_decryption_fun('encrypt',$autoGENNO);
				  $full_base=$base_root.$base_path.'admin/annual-report/step5/'.encryption_decryption_fun('encrypt',$inspectionid);
	           
	             drupal_goto($full_base);

	             }
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/annual-report/step5/'.encryption_decryption_fun('encrypt',$inspectionid);

             $message = 'DATA  NOT SAVED  . ';
                      
		   
                      drupal_set_message(t($message));
	           
	             drupal_goto($full_base);
	
     }	
	
}