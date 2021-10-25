
//For Total wages paid

	jQuery(document).ready(function() {
		$.fn.totalWagesTotalAmount = function () {
			if(jQuery("#total_wages_profit_bonus_id").val() != '') {
				var total_wages_profit_bonus = parseInt(jQuery("#total_wages_profit_bonus_id").val());
			} else {
				var total_wages_profit_bonus = 0;	
			}
			if(jQuery("#total_wages_money_value_id").val() != '') {
				var total_wages_money_value = parseInt(jQuery("#total_wages_money_value_id").val());
			} else {
				var total_wages_money_value = 0;	
			}
			if(jQuery("#total_wages_basic_wages_id").val() != '') {
				var total_wages_basic_wages = parseInt(jQuery("#total_wages_basic_wages_id").val());
			} else {
				var total_wages_basic_wages = 0;
			}
			if(jQuery("#total_wages_da_id").val() != '') {
				var total_wages_da = parseInt(jQuery("#total_wages_da_id").val());
			} else {
				var total_wages_da = 0;
			}
			if(jQuery("#total_wages_arrears_pay_id").val() != '') {
				var total_wages_arrears_pay = parseInt(jQuery("#total_wages_arrears_pay_id").val());
			} else {
				var total_wages_arrears_pay = 0;	
			}
			
			var total_wages_total_amt = total_wages_profit_bonus + total_wages_money_value + total_wages_basic_wages + total_wages_da + total_wages_arrears_pay;
			this.val(total_wages_total_amt);
		}
		
		//1
		jQuery("#total_wages_profit_bonus_id").bind('blur keyup', function(e) {
			jQuery("#total_wages_total_amt_id").totalWagesTotalAmount();
		});
		jQuery("#total_wages_profit_bonus_id").bind('change', function(e) {
			jQuery("#total_wages_total_amt_id").totalWagesTotalAmount();
		});
		
		//2
		jQuery("#total_wages_money_value_id").bind('blur keyup', function(e) {
			jQuery("#total_wages_total_amt_id").totalWagesTotalAmount();
		});
		jQuery("#total_wages_money_value_id").bind('change', function(e) {
			jQuery("#total_wages_total_amt_id").totalWagesTotalAmount();
		});
		
		//3
		jQuery("#total_wages_basic_wages_id").bind('blur keyup', function(e) {
			jQuery("#total_wages_total_amt_id").totalWagesTotalAmount();
		});
		jQuery("#total_wages_basic_wages_id").bind('change', function(e) {
			jQuery("#total_wages_total_amt_id").totalWagesTotalAmount();
		});
		
		//4
		jQuery("#total_wages_da_id").bind('blur keyup', function(e) {
			jQuery("#total_wages_total_amt_id").totalWagesTotalAmount();
		});
		jQuery("#total_wages_da_id").bind('change', function(e) {
			jQuery("#total_wages_total_amt_id").totalWagesTotalAmount();
		});
		
		//5
		jQuery("#total_wages_arrears_pay_id").bind('blur keyup', function(e) {
			jQuery("#total_wages_total_amt_id").totalWagesTotalAmount();
		});
		jQuery("#total_wages_arrears_pay_id").bind('change', function(e) {
			jQuery("#total_wages_total_amt_id").totalWagesTotalAmount();
		});
		
	});
	
	
// For Deductions

	jQuery(document).ready(function() {
		$.fn.deductionsTotalAmt = function () {
			if(jQuery("#deductions_fines_amt_realised_id").val() != '') {
				var deductions_fines_amt_realised = parseInt(jQuery("#deductions_fines_amt_realised_id").val());
			} else {
				var deductions_fines_amt_realised =	0;
			}
			if(jQuery("#deductions_damg_loss_amt_realised_id").val() != '') {
				var deductions_damg_loss_amt_realised = parseInt(jQuery("#deductions_damg_loss_amt_realised_id").val());
			} else {
				var deductions_damg_loss_amt_realised = 0;	
			}
			if(jQuery("#deductions_breach_contct_amt_realised_id").val() != '') {
				var deductions_breach_contct_amt_realised = parseInt(jQuery("#deductions_breach_contct_amt_realised_id").val());
			} else {
				var deductions_breach_contct_amt_realised = 0;	
			}
			
			var deductions_total_amt = deductions_fines_amt_realised + deductions_damg_loss_amt_realised + deductions_breach_contct_amt_realised;
			this.val(deductions_total_amt);
		}
		
		//1
		jQuery("#deductions_fines_amt_realised_id").bind('blur keyup', function(e) {
			jQuery("#deductions_total_amt_id").deductionsTotalAmt();
		});
		jQuery("#deductions_fines_amt_realised_id").bind('change', function(e) {
			jQuery("#deductions_total_amt_id").deductionsTotalAmt();
		});
		
		//2
		jQuery("#deductions_damg_loss_amt_realised_id").bind('blur keyup', function(e) {
			jQuery("#deductions_total_amt_id").deductionsTotalAmt();
		});
		jQuery("#deductions_damg_loss_amt_realised_id").bind('change', function(e) {
			jQuery("#deductions_total_amt_id").deductionsTotalAmt();
		});
		
		//3
		jQuery("#deductions_breach_contct_amt_realised_id").bind('blur keyup', function(e) {
			jQuery("#deductions_total_amt_id").deductionsTotalAmt();
		});
		jQuery("#deductions_breach_contct_amt_realised_id").bind('change', function(e) {
			jQuery("#deductions_total_amt_id").deductionsTotalAmt();
		});
		
	});
	
	
//For Fines fund

	jQuery(document).ready(function() {
		$.fn.disbursementFinesFundtotalAmt = function () {
			if(jQuery("#disbursement_a_amt_id").val() != '') {
				var disbursement_a_amt = parseInt(jQuery("#disbursement_a_amt_id").val());
			} else {
				var disbursement_a_amt = 0;	
			}
			if(jQuery("#disbursement_b_amt_id").val() != '') {
				var disbursement_b_amt = parseInt(jQuery("#disbursement_b_amt_id").val());
			} else {
				var disbursement_b_amt = 0;	
			}
			if(jQuery("#disbursement_c_amt_id").val() != '') {
				var disbursement_c_amt = parseInt(jQuery("#disbursement_c_amt_id").val());
			} else {
				var disbursement_c_amt = 0;	
			}
			if(jQuery("#disbursement_d_amt_id").val() != '') {
				var disbursement_d_amt = parseInt(jQuery("#disbursement_d_amt_id").val());
			} else {
				var disbursement_d_amt = 0;	
			}
			
			var disbursement_fines_fund_total_amt = disbursement_a_amt + disbursement_b_amt + disbursement_c_amt + disbursement_d_amt;
			this.val(disbursement_fines_fund_total_amt);
		}
		
		//1
		jQuery("#disbursement_a_amt_id").bind('blur keyup', function(e) {
			jQuery("#disbursement_fines_fund_total_amt_id").disbursementFinesFundtotalAmt();
		});
		jQuery("#disbursement_a_amt_id").bind('change', function(e) {
			jQuery("#disbursement_fines_fund_total_amt_id").disbursementFinesFundtotalAmt();
		});
		
		//2
		jQuery("#disbursement_b_amt_id").bind('blur keyup', function(e) {
			jQuery("#disbursement_fines_fund_total_amt_id").disbursementFinesFundtotalAmt();
		});
		jQuery("#disbursement_b_amt_id").bind('change', function(e) {
			jQuery("#disbursement_fines_fund_total_amt_id").disbursementFinesFundtotalAmt();
		});
		
		//3
		jQuery("#disbursement_c_amt_id").bind('blur keyup', function(e) {
			jQuery("#disbursement_fines_fund_total_amt_id").disbursementFinesFundtotalAmt();
		});
		jQuery("#disbursement_c_amt_id").bind('change', function(e) {
			jQuery("#disbursement_fines_fund_total_amt_id").disbursementFinesFundtotalAmt();
		});
		
		//4
		jQuery("#disbursement_d_amt_id").bind('blur keyup', function(e) {
			jQuery("#disbursement_fines_fund_total_amt_id").disbursementFinesFundtotalAmt();
		});
		jQuery("#disbursement_d_amt_id").bind('change', function(e) {
			jQuery("#disbursement_fines_fund_total_amt_id").disbursementFinesFundtotalAmt();
		});
		
	});
	
	
	(function($) {
 
  		Drupal.behaviors.annual_return = {
  		attach: function (context, settings) {
		 
			jQuery(".numeric_positive").keypress(function (e)  
			{
				if( e.which!=8 && e.which!=0 && (e.which<48 || e.which>57))
				{
					return false;
				}	
			});
			
			jQuery(".rs_amount").keypress(function (e)  
			{
				if( e.which!=8 && e.which!=0 && (e.which<46 || e.which == 47 || e.which>57))
				{
					return false;
				}	
			});
			
		}};
	})(jQuery);	
	
	
	
//for 4. AVERAGE DAILY NUMBER OF PERSONS EMPLOYED DURING THE YEAR of Worker Details Tab

//Per Adult Men
	jQuery(document).ready(function() {
		$.fn.avgDailyPerWorkerAdultMen = function () {
			
			//avg_daily_per_worker_adult_men
			if(jQuery("#no_days_worked_year_id").val() != '' && jQuery("#mandays_per_worker_adult_men_id").val() != '') {
				var no_days_worked_year = parseInt(jQuery("#no_days_worked_year_id").val());
				var mandays_per_worker_adult_men = parseInt(jQuery("#mandays_per_worker_adult_men_id").val());
				
				var avg_daily_per_worker_adult_men = Math.ceil(mandays_per_worker_adult_men / no_days_worked_year);
				this.val(avg_daily_per_worker_adult_men);
			
			} else {
				var no_days_worked_year = 0;
				var mandays_per_worker_adult_men = 0;
				
				var avg_daily_per_worker_adult_men = 0;
				this.val(avg_daily_per_worker_adult_men);
			}
			//end
			
		}
		
		//avg_daily_per_worker_adult_men
		jQuery("#no_days_worked_year_id").bind('blur keyup', function(e) {
			jQuery("#avg_daily_per_worker_adult_men_id").avgDailyPerWorkerAdultMen();
		});
		jQuery("#no_days_worked_year_id").bind('change', function(e) {
			jQuery("#avg_daily_per_worker_adult_men_id").avgDailyPerWorkerAdultMen();
		});
		
		jQuery("#mandays_per_worker_adult_men_id").bind('blur keyup', function(e) {
			jQuery("#avg_daily_per_worker_adult_men_id").avgDailyPerWorkerAdultMen();
		});
		jQuery("#mandays_per_worker_adult_men_id").bind('change', function(e) {
			jQuery("#avg_daily_per_worker_adult_men_id").avgDailyPerWorkerAdultMen();
		});
		//end
			
	});

//Per Adult Women	
	jQuery(document).ready(function() {
		$.fn.avgDailyPerWorkerAdultWomen = function () {
			
			//avg_daily_per_worker_adult_women
			if(jQuery("#no_days_worked_year_id").val() != '' && jQuery("#mandays_per_worker_adult_women_id").val() != '') {
				var no_days_worked_year = parseInt(jQuery("#no_days_worked_year_id").val());
				var mandays_per_worker_adult_women = parseInt(jQuery("#mandays_per_worker_adult_women_id").val());
				
				var avg_daily_per_worker_adult_women = Math.ceil(mandays_per_worker_adult_women / no_days_worked_year);
				this.val(avg_daily_per_worker_adult_women);
			
			} else {
				var no_days_worked_year = 0;
				var mandays_per_worker_adult_women = 0;
				
				var avg_daily_per_worker_adult_women = 0;
				this.val(avg_daily_per_worker_adult_women);
			}
			//end
			
		}
		
		//avg_daily_per_worker_adult_women
		jQuery("#no_days_worked_year_id").bind('blur keyup', function(e) {
			jQuery("#avg_daily_per_worker_adult_women_id").avgDailyPerWorkerAdultWomen();
		});
		jQuery("#no_days_worked_year_id").bind('change', function(e) {
			jQuery("#avg_daily_per_worker_adult_women_id").avgDailyPerWorkerAdultWomen();
		});
		
		jQuery("#mandays_per_worker_adult_women_id").bind('blur keyup', function(e) {
			jQuery("#avg_daily_per_worker_adult_women_id").avgDailyPerWorkerAdultWomen();
		});
		jQuery("#mandays_per_worker_adult_women_id").bind('change', function(e) {
			jQuery("#avg_daily_per_worker_adult_women_id").avgDailyPerWorkerAdultWomen();
		});
		//end
			
	});
	
//Per Adol Male	
	jQuery(document).ready(function() {
		$.fn.avgDailyPerWorkerAdolMale = function () {
			
			//avg_daily_per_worker_adol_male
			if(jQuery("#no_days_worked_year_id").val() != '' && jQuery("#mandays_per_worker_adol_male_id").val() != '') {
				var no_days_worked_year = parseInt(jQuery("#no_days_worked_year_id").val());
				var mandays_per_worker_adol_male = parseInt(jQuery("#mandays_per_worker_adol_male_id").val());
				
				var avg_daily_per_worker_adol_male = Math.ceil(mandays_per_worker_adol_male / no_days_worked_year);
				this.val(avg_daily_per_worker_adol_male);
			
			} else {
				var no_days_worked_year = 0;
				var mandays_per_worker_adol_male = 0;
				
				var avg_daily_per_worker_adol_male = 0;
				this.val(avg_daily_per_worker_adol_male);
			}
			//end
			
		}
		
		//avg_daily_per_worker_adol_male
		jQuery("#no_days_worked_year_id").bind('blur keyup', function(e) {
			jQuery("#avg_daily_per_worker_adol_male_id").avgDailyPerWorkerAdolMale();
		});
		jQuery("#no_days_worked_year_id").bind('change', function(e) {
			jQuery("#avg_daily_per_worker_adol_male_id").avgDailyPerWorkerAdolMale();
		});
		
		jQuery("#mandays_per_worker_adol_male_id").bind('blur keyup', function(e) {
			jQuery("#avg_daily_per_worker_adol_male_id").avgDailyPerWorkerAdolMale();
		});
		jQuery("#mandays_per_worker_adol_male_id").bind('change', function(e) {
			jQuery("#avg_daily_per_worker_adol_male_id").avgDailyPerWorkerAdolMale();
		});
		//end
			
	});
	
//Per Adol Female	
	jQuery(document).ready(function() {
		$.fn.avgDailyPerWorkerAdolFemale = function () {
			
			//avg_daily_per_worker_adol_female
			if(jQuery("#no_days_worked_year_id").val() != '' && jQuery("#mandays_per_worker_adol_female_id").val() != '') {
				var no_days_worked_year = parseInt(jQuery("#no_days_worked_year_id").val());
				var mandays_per_worker_adol_female = parseInt(jQuery("#mandays_per_worker_adol_female_id").val());
				
				var avg_daily_per_worker_adol_female = Math.ceil(mandays_per_worker_adol_female / no_days_worked_year);
				this.val(avg_daily_per_worker_adol_female);
			
			} else {
				var no_days_worked_year = 0;
				var mandays_per_worker_adol_female = 0;
				
				var avg_daily_per_worker_adol_female = 0;
				this.val(avg_daily_per_worker_adol_female);
			}
			//end
			
		}
		
		//avg_daily_per_worker_adol_female
		jQuery("#no_days_worked_year_id").bind('blur keyup', function(e) {
			jQuery("#avg_daily_per_worker_adol_female_id").avgDailyPerWorkerAdolFemale();
		});
		jQuery("#no_days_worked_year_id").bind('change', function(e) {
			jQuery("#avg_daily_per_worker_adol_female_id").avgDailyPerWorkerAdolFemale();
		});
		
		jQuery("#mandays_per_worker_adol_female_id").bind('blur keyup', function(e) {
			jQuery("#avg_daily_per_worker_adol_female_id").avgDailyPerWorkerAdolFemale();
		});
		jQuery("#mandays_per_worker_adol_female_id").bind('change', function(e) {
			jQuery("#avg_daily_per_worker_adol_female_id").avgDailyPerWorkerAdolFemale();
		});
		//end
			
	});
	
//Per Child Boys	
	jQuery(document).ready(function() {
		$.fn.avgDailyPerWorkerChildBoys = function () {
			
			//avg_daily_per_worker_child_boys
			if(jQuery("#no_days_worked_year_id").val() != '' && jQuery("#mandays_per_worker_child_boys_id").val() != '') {
				var no_days_worked_year = parseInt(jQuery("#no_days_worked_year_id").val());
				var mandays_per_worker_child_boys = parseInt(jQuery("#mandays_per_worker_child_boys_id").val());
				
				var avg_daily_per_worker_child_boys = Math.ceil(mandays_per_worker_child_boys / no_days_worked_year);
				this.val(avg_daily_per_worker_child_boys);
			
			} else {
				var no_days_worked_year = 0;
				var mandays_per_worker_child_boys = 0;
				
				var avg_daily_per_worker_child_boys = 0;
				this.val(avg_daily_per_worker_child_boys);
			}
			//end
			
		}
		
		//avg_daily_per_worker_child_boys
		jQuery("#no_days_worked_year_id").bind('blur keyup', function(e) {
			jQuery("#avg_daily_per_worker_child_boys_id").avgDailyPerWorkerChildBoys();
		});
		jQuery("#no_days_worked_year_id").bind('change', function(e) {
			jQuery("#avg_daily_per_worker_child_boys_id").avgDailyPerWorkerChildBoys();
		});
		
		jQuery("#mandays_per_worker_child_boys_id").bind('blur keyup', function(e) {
			jQuery("#avg_daily_per_worker_child_boys_id").avgDailyPerWorkerChildBoys();
		});
		jQuery("#mandays_per_worker_child_boys_id").bind('change', function(e) {
			jQuery("#avg_daily_per_worker_child_boys_id").avgDailyPerWorkerChildBoys();
		});
		//end
			
	});
	
//Per Child Girls	
	jQuery(document).ready(function() {
		$.fn.avgDailyPerWorkerChildGirls = function () {
			
			//avg_daily_per_worker_child_girls
			if(jQuery("#no_days_worked_year_id").val() != '' && jQuery("#mandays_per_worker_child_girls_id").val() != '') {
				var no_days_worked_year = parseInt(jQuery("#no_days_worked_year_id").val());
				var mandays_per_worker_child_girls = parseInt(jQuery("#mandays_per_worker_child_girls_id").val());
				
				var avg_daily_per_worker_child_girls = Math.ceil(mandays_per_worker_child_girls / no_days_worked_year);
				this.val(avg_daily_per_worker_child_girls);
			
			} else {
				var no_days_worked_year = 0;
				var mandays_per_worker_child_girls = 0;
				
				var avg_daily_per_worker_child_girls = 0;
				this.val(avg_daily_per_worker_child_girls);
			}
			//end
			
		}
		
		//avg_daily_per_worker_child_girls
		jQuery("#no_days_worked_year_id").bind('blur keyup', function(e) {
			jQuery("#avg_daily_per_worker_child_girls_id").avgDailyPerWorkerChildGirls();
		});
		jQuery("#no_days_worked_year_id").bind('change', function(e) {
			jQuery("#avg_daily_per_worker_child_girls_id").avgDailyPerWorkerChildGirls();
		});
		
		jQuery("#mandays_per_worker_child_girls_id").bind('blur keyup', function(e) {
			jQuery("#avg_daily_per_worker_child_girls_id").avgDailyPerWorkerChildGirls();
		});
		jQuery("#mandays_per_worker_child_girls_id").bind('change', function(e) {
			jQuery("#avg_daily_per_worker_child_girls_id").avgDailyPerWorkerChildGirls();
		});
		//end
			
	});
	
//Con Adult Men
	jQuery(document).ready(function() {
		$.fn.avgDailyConWorkerAdultMen = function () {
			
			//avg_daily_con_worker_adult_men
			if(jQuery("#no_days_worked_year_id").val() != '' && jQuery("#mandays_con_worker_adult_men_id").val() != '') {
				var no_days_worked_year = parseInt(jQuery("#no_days_worked_year_id").val());
				var mandays_con_worker_adult_men = parseInt(jQuery("#mandays_con_worker_adult_men_id").val());
				
				var avg_daily_con_worker_adult_men = Math.ceil(mandays_con_worker_adult_men / no_days_worked_year);
				this.val(avg_daily_con_worker_adult_men);
			
			} else {
				var no_days_worked_year = 0;
				var mandays_con_worker_adult_men = 0;
				
				var avg_daily_con_worker_adult_men = 0;
				this.val(avg_daily_con_worker_adult_men);
			}
			//end
			
		}
		
		//avg_daily_con_worker_adult_men
		jQuery("#no_days_worked_year_id").bind('blur keyup', function(e) {
			jQuery("#avg_daily_con_worker_adult_men_id").avgDailyConWorkerAdultMen();
		});
		jQuery("#no_days_worked_year_id").bind('change', function(e) {
			jQuery("#avg_daily_con_worker_adult_men_id").avgDailyConWorkerAdultMen();
		});
		
		jQuery("#mandays_con_worker_adult_men_id").bind('blur keyup', function(e) {
			jQuery("#avg_daily_con_worker_adult_men_id").avgDailyConWorkerAdultMen();
		});
		jQuery("#mandays_con_worker_adult_men_id").bind('change', function(e) {
			jQuery("#avg_daily_con_worker_adult_men_id").avgDailyConWorkerAdultMen();
		});
		//end
			
	});
	
//Con Adult Women	
	jQuery(document).ready(function() {
		$.fn.avgDailyConWorkerAdultWomen = function () {
			
			//avg_daily_con_worker_adult_women
			if(jQuery("#no_days_worked_year_id").val() != '' && jQuery("#mandays_con_worker_adult_women_id").val() != '') {
				var no_days_worked_year = parseInt(jQuery("#no_days_worked_year_id").val());
				var mandays_con_worker_adult_women = parseInt(jQuery("#mandays_con_worker_adult_women_id").val());
				
				var avg_daily_con_worker_adult_women = Math.ceil(mandays_con_worker_adult_women / no_days_worked_year);
				this.val(avg_daily_con_worker_adult_women);
			
			} else {
				var no_days_worked_year = 0;
				var mandays_con_worker_adult_women = 0;
				
				var avg_daily_con_worker_adult_women = 0;
				this.val(avg_daily_con_worker_adult_women);
			}
			//end
			
		}
		
		//avg_daily_con_worker_adult_women
		jQuery("#no_days_worked_year_id").bind('blur keyup', function(e) {
			jQuery("#avg_daily_con_worker_adult_women_id").avgDailyConWorkerAdultWomen();
		});
		jQuery("#no_days_worked_year_id").bind('change', function(e) {
			jQuery("#avg_daily_con_worker_adult_women_id").avgDailyConWorkerAdultWomen();
		});
		
		jQuery("#mandays_con_worker_adult_women_id").bind('blur keyup', function(e) {
			jQuery("#avg_daily_con_worker_adult_women_id").avgDailyConWorkerAdultWomen();
		});
		jQuery("#mandays_con_worker_adult_women_id").bind('change', function(e) {
			jQuery("#avg_daily_con_worker_adult_women_id").avgDailyConWorkerAdultWomen();
		});
		//end
			
	});
	
//Con Adol Male	
	jQuery(document).ready(function() {
		$.fn.avgDailyConWorkerAdolMale = function () {
			
			//avg_daily_con_worker_adol_male
			if(jQuery("#no_days_worked_year_id").val() != '' && jQuery("#mandays_con_worker_adol_male_id").val() != '') {
				var no_days_worked_year = parseInt(jQuery("#no_days_worked_year_id").val());
				var mandays_con_worker_adol_male = parseInt(jQuery("#mandays_con_worker_adol_male_id").val());
				
				var avg_daily_con_worker_adol_male = Math.ceil(mandays_con_worker_adol_male / no_days_worked_year);
				this.val(avg_daily_con_worker_adol_male);
			
			} else {
				var no_days_worked_year = 0;
				var mandays_con_worker_adol_male = 0;
				
				var avg_daily_con_worker_adol_male = 0;
				this.val(avg_daily_con_worker_adol_male);
			}
			//end
			
		}
		
		//avg_daily_con_worker_adol_male
		jQuery("#no_days_worked_year_id").bind('blur keyup', function(e) {
			jQuery("#avg_daily_con_worker_adol_male_id").avgDailyConWorkerAdolMale();
		});
		jQuery("#no_days_worked_year_id").bind('change', function(e) {
			jQuery("#avg_daily_con_worker_adol_male_id").avgDailyConWorkerAdolMale();
		});
		
		jQuery("#mandays_con_worker_adol_male_id").bind('blur keyup', function(e) {
			jQuery("#avg_daily_con_worker_adol_male_id").avgDailyConWorkerAdolMale();
		});
		jQuery("#mandays_con_worker_adol_male_id").bind('change', function(e) {
			jQuery("#avg_daily_con_worker_adol_male_id").avgDailyConWorkerAdolMale();
		});
		//end
			
	});
	
//Con Adol Female	
	jQuery(document).ready(function() {
		$.fn.avgDailyConWorkerAdolFemale = function () {
			
			//avg_daily_con_worker_adol_female
			if(jQuery("#no_days_worked_year_id").val() != '' && jQuery("#mandays_con_worker_adol_female_id").val() != '') {
				var no_days_worked_year = parseInt(jQuery("#no_days_worked_year_id").val());
				var mandays_con_worker_adol_female = parseInt(jQuery("#mandays_con_worker_adol_female_id").val());
				
				var avg_daily_con_worker_adol_female = Math.ceil(mandays_con_worker_adol_female / no_days_worked_year);
				this.val(avg_daily_con_worker_adol_female);
			
			} else {
				var no_days_worked_year = 0;
				var mandays_con_worker_adol_female = 0;
				
				var avg_daily_con_worker_adol_female = 0;
				this.val(avg_daily_con_worker_adol_female);
			}
			//end
			
		}
		
		//avg_daily_con_worker_adol_female
		jQuery("#no_days_worked_year_id").bind('blur keyup', function(e) {
			jQuery("#avg_daily_con_worker_adol_female_id").avgDailyConWorkerAdolFemale();
		});
		jQuery("#no_days_worked_year_id").bind('change', function(e) {
			jQuery("#avg_daily_con_worker_adol_female_id").avgDailyConWorkerAdolFemale();
		});
		
		jQuery("#mandays_con_worker_adol_female_id").bind('blur keyup', function(e) {
			jQuery("#avg_daily_con_worker_adol_female_id").avgDailyConWorkerAdolFemale();
		});
		jQuery("#mandays_con_worker_adol_female_id").bind('change', function(e) {
			jQuery("#avg_daily_con_worker_adol_female_id").avgDailyConWorkerAdolFemale();
		});
		//end
			
	});
	
//Con Child Boys	
	jQuery(document).ready(function() {
		$.fn.avgDailyConWorkerChildBoys = function () {
			
			//avg_daily_con_worker_child_boys
			if(jQuery("#no_days_worked_year_id").val() != '' && jQuery("#mandays_con_worker_child_boys_id").val() != '') {
				var no_days_worked_year = parseInt(jQuery("#no_days_worked_year_id").val());
				var mandays_con_worker_child_boys = parseInt(jQuery("#mandays_con_worker_child_boys_id").val());
				
				var avg_daily_con_worker_child_boys = Math.ceil(mandays_con_worker_child_boys / no_days_worked_year);
				this.val(avg_daily_con_worker_child_boys);
			
			} else {
				var no_days_worked_year = 0;
				var mandays_con_worker_child_boys = 0;
				
				var avg_daily_con_worker_child_boys = 0;
				this.val(avg_daily_con_worker_child_boys);
			}
			//end
			
		}
		
		//avg_daily_con_worker_child_boys
		jQuery("#no_days_worked_year_id").bind('blur keyup', function(e) {
			jQuery("#avg_daily_con_worker_child_boys_id").avgDailyConWorkerChildBoys();
		});
		jQuery("#no_days_worked_year_id").bind('change', function(e) {
			jQuery("#avg_daily_con_worker_child_boys_id").avgDailyConWorkerChildBoys();
		});
		
		jQuery("#mandays_con_worker_child_boys_id").bind('blur keyup', function(e) {
			jQuery("#avg_daily_con_worker_child_boys_id").avgDailyConWorkerChildBoys();
		});
		jQuery("#mandays_con_worker_child_boys_id").bind('change', function(e) {
			jQuery("#avg_daily_con_worker_child_boys_id").avgDailyConWorkerChildBoys();
		});
		//end
			
	});
	
//Con Child Girls	
	jQuery(document).ready(function() {
		$.fn.avgDailyConWorkerChildGirls = function () {
			
			//avg_daily_con_worker_child_girls
			if(jQuery("#no_days_worked_year_id").val() != '' && jQuery("#mandays_con_worker_child_girls_id").val() != '') {
				var no_days_worked_year = parseInt(jQuery("#no_days_worked_year_id").val());
				var mandays_con_worker_child_girls = parseInt(jQuery("#mandays_con_worker_child_girls_id").val());
				
				var avg_daily_con_worker_child_girls = Math.ceil(mandays_con_worker_child_girls / no_days_worked_year);
				this.val(avg_daily_con_worker_child_girls);
			
			} else {
				var no_days_worked_year = 0;
				var mandays_con_worker_child_girls = 0;
				
				var avg_daily_con_worker_child_girls = 0;
				this.val(avg_daily_con_worker_child_girls);
			}
			//end
			
		}
		
		//avg_daily_con_worker_child_girls
		jQuery("#no_days_worked_year_id").bind('blur keyup', function(e) {
			jQuery("#avg_daily_con_worker_child_girls_id").avgDailyConWorkerChildGirls();
		});
		jQuery("#no_days_worked_year_id").bind('change', function(e) {
			jQuery("#avg_daily_con_worker_child_girls_id").avgDailyConWorkerChildGirls();
		});
		
		jQuery("#mandays_con_worker_child_girls_id").bind('blur keyup', function(e) {
			jQuery("#avg_daily_con_worker_child_girls_id").avgDailyConWorkerChildGirls();
		});
		jQuery("#mandays_con_worker_child_girls_id").bind('change', function(e) {
			jQuery("#avg_daily_con_worker_child_girls_id").avgDailyConWorkerChildGirls();
		});
		//end
			
	});
	
	
	
//for 6. AVERAGE NUMBER OF HOURS WORKED PER WEEK of Worker Details Tab

//Per Men
	jQuery(document).ready(function() {
		$.fn.avgHrsWorkedWeekPerMen = function () {
			
			//avg_no_hrs_worked_week_per_men
			if(jQuery("#tot_no_manhrs_per_men_id").val() != '' && jQuery("#avg_daily_per_worker_adult_men_id").val() != '' && jQuery("#avg_daily_per_worker_adol_male_id").val() != '') {
				var tot_no_manhrs_per_men = parseInt(jQuery("#tot_no_manhrs_per_men_id").val());
				var avg_daily_per_worker_adult_men = parseInt(jQuery("#avg_daily_per_worker_adult_men_id").val());
				var avg_daily_per_worker_adol_male = parseInt(jQuery("#avg_daily_per_worker_adol_male_id").val());
				
				var avg_no_hrs_worked_week_per_men = Math.ceil(tot_no_manhrs_per_men / ((avg_daily_per_worker_adult_men + avg_daily_per_worker_adol_male) * 52));
				this.val(avg_no_hrs_worked_week_per_men);
			
			} else {
				var tot_no_manhrs_per_men = 0;
				var avg_daily_per_worker_adult_men = 0;
				var avg_daily_per_worker_adol_male = 0;
				
				var avg_no_hrs_worked_week_per_men = 0;
				this.val(avg_no_hrs_worked_week_per_men);
			}
			//end
			
		}
		
		//avg_no_hrs_worked_week_per_men
		jQuery("#tot_no_manhrs_per_men_id").bind('blur keyup', function(e) {
			jQuery("#avg_no_hrs_worked_week_per_men_id").avgHrsWorkedWeekPerMen();
		});
		jQuery("#tot_no_manhrs_per_men_id").bind('change', function(e) {
			jQuery("#avg_no_hrs_worked_week_per_men_id").avgHrsWorkedWeekPerMen();
		});
		
		jQuery("#avg_daily_per_worker_adult_men_id").bind('blur keyup', function(e) {
			jQuery("#avg_no_hrs_worked_week_per_men_id").avgHrsWorkedWeekPerMen();
		});
		jQuery("#avg_daily_per_worker_adult_men_id").bind('change', function(e) {
			jQuery("#avg_no_hrs_worked_week_per_men_id").avgHrsWorkedWeekPerMen();
		});
		
		jQuery("#avg_daily_per_worker_adol_male_id").bind('blur keyup', function(e) {
			jQuery("#avg_no_hrs_worked_week_per_men_id").avgHrsWorkedWeekPerMen();
		});
		jQuery("#avg_daily_per_worker_adol_male_id").bind('change', function(e) {
			jQuery("#avg_no_hrs_worked_week_per_men_id").avgHrsWorkedWeekPerMen();
		});
		//end
			
	});
	
//Per Women
	jQuery(document).ready(function() {
		$.fn.avgHrsWorkedWeekPerWomen = function () {
			
			//avg_no_hrs_worked_week_per_women
			if(jQuery("#tot_no_manhrs_per_women_id").val() != '' && jQuery("#avg_daily_per_worker_adult_women_id").val() != '' && jQuery("#avg_daily_per_worker_adol_female_id").val() != '') {
				var tot_no_manhrs_per_women = parseInt(jQuery("#tot_no_manhrs_per_women_id").val());
				var avg_daily_per_worker_adult_women = parseInt(jQuery("#avg_daily_per_worker_adult_women_id").val());
				var avg_daily_per_worker_adol_female = parseInt(jQuery("#avg_daily_per_worker_adol_female_id").val());
				
				var avg_no_hrs_worked_week_per_women = Math.ceil(tot_no_manhrs_per_women / ((avg_daily_per_worker_adult_women + avg_daily_per_worker_adol_female) * 52));
				this.val(avg_no_hrs_worked_week_per_women);
			
			} else {
				var tot_no_manhrs_per_women = 0;
				var avg_daily_per_worker_adult_women = 0;
				var avg_daily_per_worker_adol_female = 0;
				
				var avg_no_hrs_worked_week_per_women = 0;
				this.val(avg_no_hrs_worked_week_per_women);
			}
			//end
			
		}
		
		//avg_no_hrs_worked_week_per_women
		jQuery("#tot_no_manhrs_per_women_id").bind('blur keyup', function(e) {
			jQuery("#avg_no_hrs_worked_week_per_women_id").avgHrsWorkedWeekPerWomen();
		});
		jQuery("#tot_no_manhrs_per_women_id").bind('change', function(e) {
			jQuery("#avg_no_hrs_worked_week_per_women_id").avgHrsWorkedWeekPerWomen();
		});
		
		jQuery("#avg_daily_per_worker_adult_women_id").bind('blur keyup', function(e) {
			jQuery("#avg_no_hrs_worked_week_per_women_id").avgHrsWorkedWeekPerWomen();
		});
		jQuery("#avg_daily_per_worker_adult_women_id").bind('change', function(e) {
			jQuery("#avg_no_hrs_worked_week_per_women_id").avgHrsWorkedWeekPerWomen();
		});
		
		jQuery("#avg_daily_per_worker_adol_female_id").bind('blur keyup', function(e) {
			jQuery("#avg_no_hrs_worked_week_per_women_id").avgHrsWorkedWeekPerWomen();
		});
		jQuery("#avg_daily_per_worker_adol_female_id").bind('change', function(e) {
			jQuery("#avg_no_hrs_worked_week_per_women_id").avgHrsWorkedWeekPerWomen();
		});
		//end
			
	});
	
//Per Child
	jQuery(document).ready(function() {
		$.fn.avgHrsWorkedWeekPerChild = function () {
			
			//avg_no_hrs_worked_week_per_child
			if(jQuery("#tot_no_manhrs_per_child_id").val() != '' && jQuery("#avg_daily_per_worker_child_boys_id").val() != '' && jQuery("#avg_daily_per_worker_child_girls_id").val() != '') {
				var tot_no_manhrs_per_child = parseInt(jQuery("#tot_no_manhrs_per_child_id").val());
				var avg_daily_per_worker_child_boys = parseInt(jQuery("#avg_daily_per_worker_child_boys_id").val());
				var avg_daily_per_worker_child_girls = parseInt(jQuery("#avg_daily_per_worker_child_girls_id").val());
				
				var avg_no_hrs_worked_week_per_child = Math.ceil(tot_no_manhrs_per_child / ((avg_daily_per_worker_child_boys + avg_daily_per_worker_child_girls) * 52));
				this.val(avg_no_hrs_worked_week_per_child);
			
			} else {
				var tot_no_manhrs_per_child = 0;
				var avg_daily_per_worker_child_boys = 0;
				var avg_daily_per_worker_child_girls = 0;
				
				var avg_no_hrs_worked_week_per_child = 0;
				this.val(avg_no_hrs_worked_week_per_child);
			}
			//end
			
		}
		
		//avg_no_hrs_worked_week_per_child
		jQuery("#tot_no_manhrs_per_child_id").bind('blur keyup', function(e) {
			jQuery("#avg_no_hrs_worked_week_per_child_id").avgHrsWorkedWeekPerChild();
		});
		jQuery("#tot_no_manhrs_per_child_id").bind('change', function(e) {
			jQuery("#avg_no_hrs_worked_week_per_child_id").avgHrsWorkedWeekPerChild();
		});
		
		jQuery("#avg_daily_per_worker_child_boys_id").bind('blur keyup', function(e) {
			jQuery("#avg_no_hrs_worked_week_per_child_id").avgHrsWorkedWeekPerChild();
		});
		jQuery("#avg_daily_per_worker_child_boys_id").bind('change', function(e) {
			jQuery("#avg_no_hrs_worked_week_per_child_id").avgHrsWorkedWeekPerChild();
		});
		
		jQuery("#avg_daily_per_worker_child_girls_id").bind('blur keyup', function(e) {
			jQuery("#avg_no_hrs_worked_week_per_child_id").avgHrsWorkedWeekPerChild();
		});
		jQuery("#avg_daily_per_worker_child_girls_id").bind('change', function(e) {
			jQuery("#avg_no_hrs_worked_week_per_child_id").avgHrsWorkedWeekPerChild();
		});
		//end
			
	});
	
//Con Men
	jQuery(document).ready(function() {
		$.fn.avgHrsWorkedWeekConMen = function () {
			
			//avg_no_hrs_worked_week_con_men
			if(jQuery("#tot_no_manhrs_con_men_id").val() != '' && jQuery("#avg_daily_con_worker_adult_men_id").val() != '' && jQuery("#avg_daily_con_worker_adol_male_id").val() != '') {
				var tot_no_manhrs_con_men = parseInt(jQuery("#tot_no_manhrs_con_men_id").val());
				var avg_daily_con_worker_adult_men = parseInt(jQuery("#avg_daily_con_worker_adult_men_id").val());
				var avg_daily_con_worker_adol_male = parseInt(jQuery("#avg_daily_con_worker_adol_male_id").val());
				
				var avg_no_hrs_worked_week_con_men = Math.ceil(tot_no_manhrs_con_men / ((avg_daily_con_worker_adult_men + avg_daily_con_worker_adol_male) * 52));
				this.val(avg_no_hrs_worked_week_con_men);
			
			} else {
				var tot_no_manhrs_con_men = 0;
				var avg_daily_con_worker_adult_men = 0;
				var avg_daily_con_worker_adol_male = 0;
				
				var avg_no_hrs_worked_week_con_men = 0;
				this.val(avg_no_hrs_worked_week_con_men);
			}
			//end
			
		}
		
		//avg_no_hrs_worked_week_con_men
		jQuery("#tot_no_manhrs_con_men_id").bind('blur keyup', function(e) {
			jQuery("#avg_no_hrs_worked_week_con_men_id").avgHrsWorkedWeekConMen();
		});
		jQuery("#tot_no_manhrs_con_men_id").bind('change', function(e) {
			jQuery("#avg_no_hrs_worked_week_con_men_id").avgHrsWorkedWeekConMen();
		});
		
		jQuery("#avg_daily_con_worker_adult_men_id").bind('blur keyup', function(e) {
			jQuery("#avg_no_hrs_worked_week_con_men_id").avgHrsWorkedWeekConMen();
		});
		jQuery("#avg_daily_con_worker_adult_men_id").bind('change', function(e) {
			jQuery("#avg_no_hrs_worked_week_con_men_id").avgHrsWorkedWeekConMen();
		});
		
		jQuery("#avg_daily_con_worker_adol_male_id").bind('blur keyup', function(e) {
			jQuery("#avg_no_hrs_worked_week_con_men_id").avgHrsWorkedWeekConMen();
		});
		jQuery("#avg_daily_con_worker_adol_male_id").bind('change', function(e) {
			jQuery("#avg_no_hrs_worked_week_con_men_id").avgHrsWorkedWeekConMen();
		});
		//end
			
	});
	
//Con Women
	jQuery(document).ready(function() {
		$.fn.avgHrsWorkedWeekConWomen = function () {
			
			//avg_no_hrs_worked_week_con_women
			if(jQuery("#tot_no_manhrs_con_women_id").val() != '' && jQuery("#avg_daily_con_worker_adult_women_id").val() != '' && jQuery("#avg_daily_con_worker_adol_female_id").val() != '') {
				var tot_no_manhrs_con_women = parseInt(jQuery("#tot_no_manhrs_con_women_id").val());
				var avg_daily_con_worker_adult_women = parseInt(jQuery("#avg_daily_con_worker_adult_women_id").val());
				var avg_daily_con_worker_adol_female = parseInt(jQuery("#avg_daily_con_worker_adol_female_id").val());
				
				var avg_no_hrs_worked_week_con_women = Math.ceil(tot_no_manhrs_con_women / ((avg_daily_con_worker_adult_women + avg_daily_con_worker_adol_female) * 52));
				this.val(avg_no_hrs_worked_week_con_women);
			
			} else {
				var tot_no_manhrs_con_women = 0;
				var avg_daily_con_worker_adult_women = 0;
				var avg_daily_con_worker_adol_female = 0;
				
				var avg_no_hrs_worked_week_con_women = 0;
				this.val(avg_no_hrs_worked_week_con_women);
			}
			//end
			
		}
		
		//avg_no_hrs_worked_week_con_women
		jQuery("#tot_no_manhrs_con_women_id").bind('blur keyup', function(e) {
			jQuery("#avg_no_hrs_worked_week_con_women_id").avgHrsWorkedWeekConWomen();
		});
		jQuery("#tot_no_manhrs_con_women_id").bind('change', function(e) {
			jQuery("#avg_no_hrs_worked_week_con_women_id").avgHrsWorkedWeekConWomen();
		});
		
		jQuery("#avg_daily_con_worker_adult_women_id").bind('blur keyup', function(e) {
			jQuery("#avg_no_hrs_worked_week_con_women_id").avgHrsWorkedWeekConWomen();
		});
		jQuery("#avg_daily_con_worker_adult_women_id").bind('change', function(e) {
			jQuery("#avg_no_hrs_worked_week_con_women_id").avgHrsWorkedWeekConWomen();
		});
		
		jQuery("#avg_daily_con_worker_adol_female_id").bind('blur keyup', function(e) {
			jQuery("#avg_no_hrs_worked_week_con_women_id").avgHrsWorkedWeekConWomen();
		});
		jQuery("#avg_daily_con_worker_adol_female_id").bind('change', function(e) {
			jQuery("#avg_no_hrs_worked_week_con_women_id").avgHrsWorkedWeekConWomen();
		});
		//end
			
	});
	
//Con Child
	jQuery(document).ready(function() {
		$.fn.avgHrsWorkedWeekConChild = function () {
			
			//avg_no_hrs_worked_week_con_child
			if(jQuery("#tot_no_manhrs_con_child_id").val() != '' && jQuery("#avg_daily_con_worker_child_boys_id").val() != '' && jQuery("#avg_daily_con_worker_child_girls_id").val() != '') {
				var tot_no_manhrs_con_child = parseInt(jQuery("#tot_no_manhrs_con_child_id").val());
				var avg_daily_con_worker_child_boys = parseInt(jQuery("#avg_daily_con_worker_child_boys_id").val());
				var avg_daily_con_worker_child_girls = parseInt(jQuery("#avg_daily_con_worker_child_girls_id").val());
				
				var avg_no_hrs_worked_week_con_child = Math.ceil(tot_no_manhrs_con_child / ((avg_daily_con_worker_child_boys + avg_daily_con_worker_child_girls) * 52));
				this.val(avg_no_hrs_worked_week_con_child);
			
			} else {
				var tot_no_manhrs_con_child = 0;
				var avg_daily_con_worker_child_boys = 0;
				var avg_daily_con_worker_child_girls = 0;
				
				var avg_no_hrs_worked_week_con_child = 0;
				this.val(avg_no_hrs_worked_week_con_child);
			}
			//end
			
		}
		
		//avg_no_hrs_worked_week_con_child
		jQuery("#tot_no_manhrs_con_child_id").bind('blur keyup', function(e) {
			jQuery("#avg_no_hrs_worked_week_con_child_id").avgHrsWorkedWeekConChild();
		});
		jQuery("#tot_no_manhrs_con_child_id").bind('change', function(e) {
			jQuery("#avg_no_hrs_worked_week_con_child_id").avgHrsWorkedWeekConChild();
		});
		
		jQuery("#avg_daily_con_worker_child_boys_id").bind('blur keyup', function(e) {
			jQuery("#avg_no_hrs_worked_week_con_child_id").avgHrsWorkedWeekConChild();
		});
		jQuery("#avg_daily_con_worker_child_boys_id").bind('change', function(e) {
			jQuery("#avg_no_hrs_worked_week_con_child_id").avgHrsWorkedWeekConChild();
		});
		
		jQuery("#avg_daily_con_worker_child_girls_id").bind('blur keyup', function(e) {
			jQuery("#avg_no_hrs_worked_week_con_child_id").avgHrsWorkedWeekConChild();
		});
		jQuery("#avg_daily_con_worker_child_girls_id").bind('change', function(e) {
			jQuery("#avg_no_hrs_worked_week_con_child_id").avgHrsWorkedWeekConChild();
		});
		//end
			
	});
	

	
	function maternity_benefit_checking() {
		
		if(jQuery("#edit-maternity-benefit-flag").is(':checked')) {
			var flagVal = confirm('Are you sure want to submit the form selecting Maternity Benefit Rules Return? You have to submit the Maternity Benefit Rules Return.');
			
			if(flagVal == true) {
				return true;
			} else {
				return false;
			}
			
		} else if(jQuery("#edit-maternity-benefit-flag").not(':checked')) {
			var flagVal = confirm('Are you sure want to submit the form without selecting Maternity Benefit Rules Return?');
			
			if(flagVal == true) {
				return true;
			} else {
				return false;
			}
			
		}
		
	}
		
//Starting of Client-side validation of Annual Return

	function validate_annual_return_common_form() {
		//alert('ok');
		var formElements =
		{
			
			//"annual_return_year":["Annual Return Year", "selectBox"],
			"factory_id":["Choose Factory Licence No.", "selectBox"],
			/*"factory_name":["Enter Registered Factory Name", "factoryName"],
			"pincode":["Factory Address Pincode", "onlyNo"],
			"state":["Factory Address State", "selectBox"],
			"district":["Factory Address District", "selectBox"],
			"subdivision":["Factory Address Sub-Division", "selectBox"],
			"areatype":["Factory Address Area Type", "selectBox"],
			"block":["Factory Address Block / Municipality / Corporation / Notified Area / SEZ", "selectBox"],
			"panchayat":["Factory Address Gram Panchayat / Ward / Sector", "selectBox"],
			"policestation":["Factory Address Police Station", "selectBox"],
			"postoffice":["Factory Address Post Office", "selectBox"],
			"factory_zone_name":["Factory Zone", "hyphenFullStop"],
			"nearest_landmark":["Nearest Landmark", "onlyAlphabet"],
			"addrline":["Factory Address", "streetAddress"],
			"industry_nature":["Nature of Industry", "hyphenFullStopAmpersand"],
			"registration_number":["Registration No.", "factoryRegNo"],
			"registration_date":["Registration Date", "date"],
			"licence_number":["Licence No.", "onlyNo"],
			"licence_date":["Licence Date", "date"],
			"classification_no":["Classification No.", "factoryClassifNo"],*/
			"occupier_name":["Occupier Name","alphabetFullstop"],
			"pincodeoprmntadr":["Occupier Address Pincode", "onlyNo"],
			"state_oprmntadr":["Occupier Address State", "selectBox"],
			"district_oprmntadr":["Occupier Address District", "selectBox"],
			"subdivision_oprmntadr":["Occupier Address Sub-Division", "selectBox"],
			"areatype_oprmntadr":["Occupier Address Area Type", "selectBox"],
			"block_oprmntadr":["Occupier Address Block / Municipality / Corporation / Notified Area / SEZ", "selectBox"],
			"panchayat_oprmntadr":["Occupier Address Gram Panchayat / Ward / Sector", "selectBox"],
			"policestation_oprmntadr":["Occupier Address Police Station", "selectBox"],
			"postoffice_oprmntadr":["Occupier Address Post Office", "selectBox"],
			"addrline_oprmntadr":["Occupier Address", "streetAddress"],
			"manager_name":["Manager Name","alphabetFullstop"],
			"pincode_manager":["Manager Address Pincode", "onlyNo"],
			"state_manager":["Manager Address State", "selectBox"],
			"district_manager":["Manager Address District", "selectBox"],
			"sub_division_manager":["Manager Address Sub-Division", "selectBox"],
			"area_type_manager":["Manager Address Area Type", "selectBox"],
			"block_mun_cor_sez_not_manager":["Manager Address Block / Municipality / Corporation / Notified Area / SEZ", "selectBox"],
			"grm_ward_sector_not_manager":["Manager Address Gram Panchayat / Ward / Sector", "selectBox"],
			"police_station_manager":["Manager Address Police Station", "selectBox"],
			"post_office_manager":["Manager Address Post Office", "selectBox"],
			"adress_line1_manager":["Manager Address", "streetAddress"],
			
		};	
	
		if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}
	}
	
	
	/*function validate_occupier_details_form() {
		//alert('ok');
		var formElements1 =
		{
			
			"occupier_name_upd":["Occupier Name","alphabetFullstop"],
			"pincodeoprmntadr_upd":["Occupier Address Pincode", "onlyNo"],
			"state_oprmntadr_upd":["Occupier Address State", "selectBox"],
			"district_oprmntadr_upd":["Occupier Address District", "selectBox"],
			"subdivision_oprmntadr_upd":["Occupier Address Sub-Division", "selectBox"],
			"areatype_oprmntadr_upd":["Occupier Address Area Type", "selectBox"],
			"block_oprmntadr_upd":["Occupier Address Block / Municipality / Corporation / Notified Area / SEZ", "selectBox"],
			"panchayat_oprmntadr_upd":["Occupier Address Gram Panchayat / Ward / Sector", "selectBox"],
			"policestation_oprmntadr_upd":["Occupier Address Police Station", "selectBox"],
			"postoffice_oprmntadr_upd":["Occupier Address Post Office", "selectBox"],
			"addrline_oprmntadr_upd":["Occupier Address", "streetAddress"],
			
		};
	
		if(!validateForm(formElements1)) {alert('ok1');
			return false;
		} else {alert('ok2');
			return true;
		}
	}*/
	
	
	function validate_workers_details_form() {
		//alert('ok');
		var formElements =
		{
			
			"no_days_worked_year":["Number of days worked during the year", "onlyNo"],
			
			"mandays_per_worker_adult_men":["Mandays Permanent Worker Adult Men", "onlyNo"],
			"mandays_per_worker_adult_women":["Mandays Permanent Worker Adult Women", "onlyNo"],
			"mandays_per_worker_adol_male":["Mandays Permanent Worker Adolescents Male", "onlyNo"],
			"mandays_per_worker_adol_male":["Mandays Permanent Worker Adolescents Female", "onlyNo"],
			"mandays_per_worker_child_boys":["Mandays Permanent Worker Children Boys", "onlyNo"],
			"mandays_per_worker_child_girls":["Mandays Permanent Worker Children Girls", "onlyNo"],
			"mandays_con_worker_adult_men":["Mandays Contractual Worker Adult Men", "onlyNo"],
			"mandays_con_worker_adult_women":["Mandays Contractual Worker Adult Women", "onlyNo"],
			"mandays_con_worker_adol_male":["Mandays Contractual Worker Adolescents Male", "onlyNo"],
			"mandays_con_worker_adol_male":["Mandays Contractual Worker Adolescents Female", "onlyNo"],
			"mandays_con_worker_child_boys":["Mandays Contractual Worker Children Boys", "onlyNo"],
			"mandays_con_worker_child_girls":["Mandays Contractual Worker Children Girls", "onlyNo"],
			
			"avg_daily_per_worker_adult_men":["Average Daily Permanent Worker Adult Men", "onlyNo"],
			"avg_daily_per_worker_adult_women":["Average Daily Permanent Worker Adult Women", "onlyNo"],
			"avg_daily_per_worker_adol_male":["Average Daily Permanent Worker Adolescents Male", "onlyNo"],
			"avg_daily_per_worker_adol_male":["Average Daily Permanent Worker Adolescents Female", "onlyNo"],
			"avg_daily_per_worker_child_boys":["Average Daily Permanent Worker Children Boys", "onlyNo"],
			"avg_daily_per_worker_child_girls":["Average Daily Permanent Worker Children Girls", "onlyNo"],
			"avg_daily_con_worker_adult_men":["Average Daily Contractual Worker Adult Men", "onlyNo"],
			"avg_daily_con_worker_adult_women":["Average Daily Contractual Worker Adult Women", "onlyNo"],
			"avg_daily_con_worker_adol_male":["Average Daily Contractual Worker Adolescents Male", "onlyNo"],
			"avg_daily_con_worker_adol_male":["Average Daily Contractual Worker Adolescents Female", "onlyNo"],
			"avg_daily_con_worker_child_boys":["Average Daily Contractual Worker Children Boys", "onlyNo"],
			"avg_daily_con_worker_child_girls":["Average Daily Contractual Worker Children Girls", "onlyNo"],
			
			"tot_no_manhrs_per_men":["Total No. Manhours Permanent Men", "onlyNo"],
			"tot_no_manhrs_per_women":["Total No. Manhours Permanent Women", "onlyNo"],
			"tot_no_manhrs_per_child":["Total No. Manhours Permanent Children", "onlyNo"],
			"tot_no_manhrs_con_men":["Total No. Manhours Contractual Men", "onlyNo"],
			"tot_no_manhrs_con_women":["Total No. Manhours Contractual Women", "onlyNo"],
			"tot_no_manhrs_con_child":["Total No. Manhours Contractual Children", "onlyNo"],
			
			"avg_no_hrs_worked_week_per_men":["Average No. Hours Worked Permanent Men", "onlyNo"],
			"avg_no_hrs_worked_week_per_women":["Average No. Hours Worked Permanent Women", "onlyNo"],
			"avg_no_hrs_worked_week_per_child":["Average No. Hours Worked Permanent Children", "onlyNo"],
			"avg_no_hrs_worked_week_con_men":["Average No. Hours Worked Contractual Men", "onlyNo"],
			"avg_no_hrs_worked_week_con_women":["Average No. Hours Worked Contractual Women", "onlyNo"],
			"avg_no_hrs_worked_week_con_child":["Average No. Hours Worked Contractual Children", "onlyNo"],
			
		};
	
		if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}
	}
	
	
	function validate_leave_wages_form() {
		//alert('ok');
		var formElements =
		{
			
			"tot_no_workers_year_per_men":["Total No. Workers During Year Permanent Men", "onlyNo"],
			"tot_no_workers_year_per_women":["Total No. Workers During Year Permanent Women", "onlyNo"],
			"tot_no_workers_year_per_child":["Total No. Workers During Year Permanent Children", "onlyNo"],
			"tot_no_workers_year_con_men":["Total No. Workers During Year Contractual Men", "onlyNo"],
			"tot_no_workers_year_con_women":["Total No. Workers During Year Contractual Women", "onlyNo"],
			"tot_no_workers_year_con_child":["Total No. Workers During Year Contractual Children", "onlyNo"],
			
			"no_workers_annual_leave_per_men":["No. Workers Annual Leave Permanent Men", "onlyNo"],
			"no_workers_annual_leave_per_women":["No. Workers Annual Leave Permanent Women", "onlyNo"],
			"no_workers_annual_leave_per_child":["No. Workers Annual Leave Permanent Children", "onlyNo"],
			"no_workers_annual_leave_con_men":["No. Workers Annual Leave Contractual Men", "onlyNo"],
			"no_workers_annual_leave_con_women":["No. Workers Annual Leave Contractual Women", "onlyNo"],
			"no_workers_annual_leave_con_child":["No. Workers Annual Leave Contractual Children", "onlyNo"],
			
			"no_workers_granted_leave_per_men":["No. Workers Granted Leave Permanent Men", "onlyNo"],
			"no_workers_granted_leave_per_women":["No. Workers Granted Leave Permanent Women", "onlyNo"],
			"no_workers_granted_leave_per_child":["No. Workers Granted Leave Permanent Children", "onlyNo"],
			"no_workers_granted_leave_con_men":["No. Workers Granted Leave Contractual Men", "onlyNo"],
			"no_workers_granted_leave_con_women":["No. Workers Granted Leave Contractual Women", "onlyNo"],
			"no_workers_granted_leave_con_child":["No. Workers Granted Leave Contractual Children", "onlyNo"],
			
			"no_workers_discharged_permanent":["No. Workers Discharged Permanent", "onlyNo"],
			"no_workers_discharged_contractual":["No. Workers Discharged Contractual", "onlyNo"],
			
			"no_workers_lieu_leave_permanent":["No. Workers Lieu Leave Permanent", "onlyNo"],
			"no_workers_lieu_leave_contractual":["No. Workers Lieu Leave Contractual", "onlyNo"],
			
		};
	
		if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}
	}
	
	
	function validate_payment_wages_return_form() {
		//alert('ok');
		var formElements =
		{
			
			"total_wages_profit_bonus":["Profit sharing bonus Rs.", "rsAmount"],
			"total_wages_money_value":["Money value of concessions Rs.", "rsAmount"],
			"total_wages_basic_wages":["Basic wages including overtime and non-profit sharing bonus Rs.", "rsAmount"],
			"total_wages_da":["Dearness and other allowances Rs.", "rsAmount"],
			"total_wages_arrears_pay":["Arrears of pay in respect of the previous years paid during the year Rs.", "rsAmount"],
			"total_wages_total_amt":["Total wages paid Total Rs.", "rsAmount"],
			
			"deductions_fines_no_cases":["Deductions Fines Number of cases", "onlyNo"],
			"deductions_fines_amt_realised":["Deductions Fines Amount realised Rs.", "rsAmount"],
			"deductions_damg_loss_no_cases":["Deductions for damage or loss Number of cases", "onlyNo"],
			"deductions_damg_loss_amt_realised":["Deductions for damage or loss Amount realised Rs.", "rsAmount"],
			"deductions_breach_contct_no_cases":["Deduction for breach of contract Number of cases", "onlyNo"],
			"deductions_breach_contct_amt_realised":["Deduction for breach of contract Amount realised Rs.", "rsAmount"],
			"deductions_total_amt":["Deductions Total Amount realised Rs.", "rsAmount"],
			
			"balance_fines_fund_beginning_year":["Balance of fines fund in hand at the beginning of the year Rs.", "rsAmount"],
			"disbursement_a_purpose":["Disbursement from fine funds Purpose (a)", "alphabetFullstop"],
			"disbursement_a_amt":["Disbursement from fine funds 	Amount (a)", "rsAmount"],
			"disbursement_b_purpose":["Disbursement from fine funds Purpose (b)", "alphabetFullstop"],
			"disbursement_b_amt":["Disbursement from fine funds 	Amount (b)", "rsAmount"],
			"disbursement_c_purpose":["Disbursement from fine funds Purpose (c)", "alphabetFullstop"],
			"disbursement_c_amt":["Disbursement from fine funds 	Amount (c)", "rsAmount"],
			"disbursement_d_purpose":["Disbursement from fine funds Purpose (d)", "alphabetFullstop"],
			"disbursement_d_amt":["Disbursement from fine funds 	Amount (d)", "rsAmount"],
			"disbursement_fines_fund_total_amt":["Disbursement from fine funds Total Amount", "rsAmount"],
			"balance_fines_fund_end_year":["Balance of fines fund in hand at the end of the year Rs. ", "rsAmount"],
		};
	
		if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}
	}