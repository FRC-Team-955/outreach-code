#include "Robot.h"
#include <iostream>
#include "ctre/Phoenix.h"
#include "frc/WPILib.h"
#include <frc/Joystick.h>


using namespace frc;
//using namespace std::chrono;

Joystick *joy0;

TalonSRX *talon_left_enc;
TalonSRX *talon_left_noenc;
TalonSRX *talon_right_enc; 
TalonSRX *talon_right_noenc;
TalonSRX *talon_elevator;

float move = 0;
float turn = 0;

void Robot::RobotInit() {
	joy0 = new Joystick(0);

	talon_left_noenc = new TalonSRX(10);
	talon_left_enc = new TalonSRX(6);
	talon_right_noenc = new TalonSRX(9);
	talon_right_enc = new TalonSRX(7);
	talon_elevator = new TalonSRX(8);
	talon_left_noenc->Set(ControlMode::Follower, 6);
	talon_right_noenc->Set(ControlMode::Follower, 7);
	std::cout<<"Outreach v. 2"<<std::endl;
	}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
}

void Robot::AutonomousPeriodic() {
}

void Robot::TeleopInit() {
}

void Robot::TeleopPeriodic() {
	move = -1 *joy0->GetRawAxis( 1 );
	turn = joy0->GetRawAxis( 4 );
	std::cout<<"Move: "<<move<<std::endl;
	std::cout<<"Turn: "<<turn<<std::endl;

	// skew the values to get tiny motion with the belly of the joystick range and high values at the extremes
	move = pow(move, 5);
	turn = pow(turn, 5);

	//std::cout<<"\tskewed move = "<<move<<"\tskewed turn = "<<turn;

	// scale the values based on the max allowed speed
	move *= 0.2;
	turn *= 0.2;

	// write to motors
	talon_left_enc->Set(ControlMode::PercentOutput,  move+turn);
	talon_right_enc->Set(ControlMode::PercentOutput, -move+turn);
	std::cout<<"Right Enc: "<<talon_right_enc->GetOutputCurrent()<<std::endl;
	std::cout<<"Left Enc: "<<talon_left_enc->GetOutputCurrent()<<std::endl;
	std::cout<<"Right Noenc: "<<talon_right_noenc->GetOutputCurrent()<<std::endl;
	std::cout<<"Left Noenc: "<<talon_left_noenc->GetOutputCurrent()<<std::endl;
	std::cout<<"Elevator: "<<talon_elevator->GetOutputCurrent()<<std::endl;

	//Change the axis if you want a different one
	if (joy0->GetRawAxis(3) > 0.2)
	{
		talon_elevator->Set(ControlMode::PercentOutput, 0.4);
	}
	else if (joy0->GetRawAxis(4) > 0.2) {
		talon_elevator->Set(ControlMode::PercentOutput, -0.4);
	}
	else{
		//If you want elevator to maintain a bit of power while you aren't trying to move it
		// Put that here
		std::cout<<"Elevator not moving"<<std::endl;

	}
}

void Robot::TestPeriodic() {}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
