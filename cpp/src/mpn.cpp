#include <ompl/base/StateSpace.h>
#include <ompl/base/ScopedState.h>
#include <ompl/base/SpaceInformation.h>
#include <ompl/base/ProblemDefinition.h>
#include <ompl/base/Planner.h>
#include <ompl/base/goals/GoalStates.h>
#include <ompl/base/goals/GoalState.h>
#include <ompl/geometric/PathGeometric.h>


#include <mpn.h>

ompl::base::PlannerStatus ompl::geometric::MPN::solve(const base::PlannerTerminationCondition &ptc)
{

    // get the problem definition
    base::ProblemDefinitionPtr pdef = getProblemDefinition();
    base::StateSpacePtr space = si_->getStateSpace();

    // get the start and goal states
    const base::State *start_state = pdef->getStartState(0);
    const base::State* goal_state = pdef->getGoal()->as<ompl::base::GoalState>()->getState();

    // get the state dimension
    unsigned int dim = space->getDimension();

    // create a new path
    auto path(std::make_shared<PathGeometric>(si_));

    // create the start state
    ompl::base::ScopedState<> start(space);
    start = start_state;

    // create the goal state
    ompl::base::ScopedState<> goal(space);
    goal = goal_state;

    if(!si_->isValid(start.get())) std::cout<<"start invalid"<<std::endl;


    // // check if the connection between start and goal states is valid
    bool connection_valid = si_->checkMotion(start_state, goal_state);

    if(connection_valid)
    {
        std::cout << "The connection between start and goal states is valid." << std::endl;
    }
    else
    {
        std::cout << "The connection between start and goal states is invalid." << std::endl;
    }

    // add the start state to the path
    path->append(start.get());

    // add the goal state to the path
    path->append(goal.get());

    // add the path to the problem definition
    pdef->addSolutionPath(path);

    // this->time_o = 50;

    std::cout<<"before"<<this->time_o<<std::endl;
    this->time_o = 50;
    std::cout<<"after"<<this->time_o<<std::endl;
    std::cout<<"This is the MPN, Finished!"<<std::endl;

    // return the status
    return base::PlannerStatus::EXACT_SOLUTION;
}