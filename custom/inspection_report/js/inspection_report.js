
//For Total number of male workers employed

	jQuery(document).ready(function() {
		$.fn.totalMaleWorkers = function () {
			if(jQuery("#per_workers_male_id").val() != '') {
				var per_workers_male = parseInt(jQuery("#per_workers_male_id").val());
			} else {
				var per_workers_male = 0;	
			}
			if(jQuery("#staff_male_id").val() != '') {
				var staff_male = parseInt(jQuery("#staff_male_id").val());
			} else {
				var staff_male = 0;	
			}
			if(jQuery("#con_workers_male_id").val() != '') {
				var con_workers_male = parseInt(jQuery("#con_workers_male_id").val());
			} else {
				var con_workers_male = 0;	
			}
			if(jQuery("#daily_wages_male_id").val() != '') {
				var daily_wages_male = parseInt(jQuery("#daily_wages_male_id").val());
			} else {
				var daily_wages_male = 0;	
			}
			if(jQuery("#temporary_male_id").val() != '') {
				var temporary_male = parseInt(jQuery("#temporary_male_id").val());
			} else {
				var temporary_male = 0;	
			}
			if(jQuery("#security_male_id").val() != '') {
				var security_male = parseInt(jQuery("#security_male_id").val());
			} else {
				var security_male = 0;	
			}
			if(jQuery("#trainee_male_id").val() != '') {
				var trainee_male = parseInt(jQuery("#trainee_male_id").val());
			} else {
				var trainee_male = 0;	
			}
			if(jQuery("#adolescent_male_id").val() != '') {
				var adolescent_male = parseInt(jQuery("#adolescent_male_id").val());
			} else {
				var adolescent_male = 0;	
			}
			
			var tot_no_workers_total_male = per_workers_male + staff_male + con_workers_male + daily_wages_male + temporary_male + security_male + trainee_male + adolescent_male;
			this.val(tot_no_workers_total_male);
		}
		
		//Permanent Workers
		jQuery("#per_workers_male_id").bind('blur keyup', function(e) {
			jQuery("#tot_no_workers_total_male_id").totalMaleWorkers();
		});
		jQuery("#per_workers_male_id").bind('change', function(e) {
			jQuery("#tot_no_workers_total_male_id").totalMaleWorkers();
		});
		
		//Staff
		jQuery("#staff_male_id").bind('blur keyup', function(e) {
			jQuery("#tot_no_workers_total_male_id").totalMaleWorkers();
		});
		jQuery("#staff_male_id").bind('change', function(e) {
			jQuery("#tot_no_workers_total_male_id").totalMaleWorkers();
		});
		
		//Contract Workers
		jQuery("#con_workers_male_id").bind('blur keyup', function(e) {
			jQuery("#tot_no_workers_total_male_id").totalMaleWorkers();
		});
		jQuery("#con_workers_male_id").bind('change', function(e) {
			jQuery("#tot_no_workers_total_male_id").totalMaleWorkers();
		});
		
		//Daily Wages
		jQuery("#daily_wages_male_id").bind('blur keyup', function(e) {
			jQuery("#tot_no_workers_total_male_id").totalMaleWorkers();
		});
		jQuery("#daily_wages_male_id").bind('change', function(e) {
			jQuery("#tot_no_workers_total_male_id").totalMaleWorkers();
		});
		
		//Temporary
		jQuery("#temporary_male_id").bind('blur keyup', function(e) {
			jQuery("#tot_no_workers_total_male_id").totalMaleWorkers();
		});
		jQuery("#temporary_male_id").bind('change', function(e) {
			jQuery("#tot_no_workers_total_male_id").totalMaleWorkers();
		});
		
		//Watchman/Security
		jQuery("#security_male_id").bind('blur keyup', function(e) {
			jQuery("#tot_no_workers_total_male_id").totalMaleWorkers();
		});
		jQuery("#security_male_id").bind('change', function(e) {
			jQuery("#tot_no_workers_total_male_id").totalMaleWorkers();
		});
		
		//Apprentice/Trainee
		jQuery("#trainee_male_id").bind('blur keyup', function(e) {
			jQuery("#tot_no_workers_total_male_id").totalMaleWorkers();
		});
		jQuery("#trainee_male_id").bind('change', function(e) {
			jQuery("#tot_no_workers_total_male_id").totalMaleWorkers();
		});
		
		//Adolescent
		jQuery("#adolescent_male_id").bind('blur keyup', function(e) {
			jQuery("#tot_no_workers_total_male_id").totalMaleWorkers();
		});
		jQuery("#adolescent_male_id").bind('change', function(e) {
			jQuery("#tot_no_workers_total_male_id").totalMaleWorkers();
		});
		
	});
	
	
//For Total number of female workers employed

	jQuery(document).ready(function() {
		$.fn.totalFemaleWorkers = function () {
			if(jQuery("#per_workers_female_id").val() != '') {
				var per_workers_female = parseInt(jQuery("#per_workers_female_id").val());
			} else {
				var per_workers_female = 0;	
			}
			if(jQuery("#staff_female_id").val() != '') {
				var staff_female = parseInt(jQuery("#staff_female_id").val());
			} else {
				var staff_female = 0;	
			}
			if(jQuery("#con_workers_female_id").val() != '') {
				var con_workers_female = parseInt(jQuery("#con_workers_female_id").val());
			} else {
				var con_workers_female = 0;	
			}
			if(jQuery("#daily_wages_female_id").val() != '') {
				var daily_wages_female = parseInt(jQuery("#daily_wages_female_id").val());
			} else {
				var daily_wages_female = 0;	
			}
			if(jQuery("#temporary_female_id").val() != '') {
				var temporary_female = parseInt(jQuery("#temporary_female_id").val());
			} else {
				var temporary_female = 0;	
			}
			if(jQuery("#security_female_id").val() != '') {
				var security_female = parseInt(jQuery("#security_female_id").val());
			} else {
				var security_female = 0;	
			}
			if(jQuery("#trainee_female_id").val() != '') {
				var trainee_female = parseInt(jQuery("#trainee_female_id").val());
			} else {
				var trainee_female = 0;	
			}
			if(jQuery("#adolescent_female_id").val() != '') {
				var adolescent_female = parseInt(jQuery("#adolescent_female_id").val());
			} else {
				var adolescent_female = 0;	
			}
			
			var tot_no_workers_total_female = per_workers_female + staff_female + con_workers_female + daily_wages_female + temporary_female + security_female + trainee_female + adolescent_female;
			this.val(tot_no_workers_total_female);
		}
		
		//Permanent Workers
		jQuery("#per_workers_female_id").bind('blur keyup', function(e) {
			jQuery("#tot_no_workers_total_female_id").totalFemaleWorkers();
		});
		jQuery("#per_workers_female_id").bind('change', function(e) {
			jQuery("#tot_no_workers_total_female_id").totalFemaleWorkers();
		});
		
		//Staff
		jQuery("#staff_female_id").bind('blur keyup', function(e) {
			jQuery("#tot_no_workers_total_female_id").totalFemaleWorkers();
		});
		jQuery("#staff_female_id").bind('change', function(e) {
			jQuery("#tot_no_workers_total_female_id").totalFemaleWorkers();
		});
		
		//Contract Workers
		jQuery("#con_workers_female_id").bind('blur keyup', function(e) {
			jQuery("#tot_no_workers_total_female_id").totalFemaleWorkers();
		});
		jQuery("#con_workers_female_id").bind('change', function(e) {
			jQuery("#tot_no_workers_total_female_id").totalFemaleWorkers();
		});
		
		//Daily Wages
		jQuery("#daily_wages_female_id").bind('blur keyup', function(e) {
			jQuery("#tot_no_workers_total_female_id").totalFemaleWorkers();
		});
		jQuery("#daily_wages_female_id").bind('change', function(e) {
			jQuery("#tot_no_workers_total_female_id").totalFemaleWorkers();
		});
		
		//Temporary
		jQuery("#temporary_female_id").bind('blur keyup', function(e) {
			jQuery("#tot_no_workers_total_female_id").totalFemaleWorkers();
		});
		jQuery("#temporary_female_id").bind('change', function(e) {
			jQuery("#tot_no_workers_total_female_id").totalFemaleWorkers();
		});
		
		//Watchman/Security
		jQuery("#security_female_id").bind('blur keyup', function(e) {
			jQuery("#tot_no_workers_total_female_id").totalFemaleWorkers();
		});
		jQuery("#security_female_id").bind('change', function(e) {
			jQuery("#tot_no_workers_total_female_id").totalFemaleWorkers();
		});
		
		//Apprentice/Trainee
		jQuery("#trainee_female_id").bind('blur keyup', function(e) {
			jQuery("#tot_no_workers_total_female_id").totalFemaleWorkers();
		});
		jQuery("#trainee_female_id").bind('change', function(e) {
			jQuery("#tot_no_workers_total_female_id").totalFemaleWorkers();
		});
		
		//Adolescent
		jQuery("#adolescent_female_id").bind('blur keyup', function(e) {
			jQuery("#tot_no_workers_total_female_id").totalFemaleWorkers();
		});
		jQuery("#adolescent_female_id").bind('change', function(e) {
			jQuery("#tot_no_workers_total_female_id").totalFemaleWorkers();
		});
		
	});