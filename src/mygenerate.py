#!/usr/bin/env python3
# -*- encoding:utf-8 -*-

from planning import *
from utility import *
import sys
import os
if __name__ == '__main__':
    # print("当前的工作目录:",os.getcwd())

    type =  "Rigidbody_2D"
    vis = "./myfig/S2D_Rigidbody"
    path_save_file = "./Data/S2D_Rigidbody_Path_"
    s_g_file = "./Data/S2D/S2D_RB_sg_ev_not_trivial.npy"
    env_file = "./Data/S2D/S2D_env_100_rec.npy"

    # load env
    rec_envs = np.load(env_file, allow_pickle=True)
    # print("envs shape:", rec_envs.shape)
    pl = Plan(type,"MPN", set_bounds=(-20, 20))
    g_s_g = 0
    # generate start and goal
    if g_s_g:
        generate_start_goal(pl=pl,rec_envs=rec_envs,cnt=(1000,400),s_g_file=s_g_file,rm_trivial=True)
        # load start goal
    else:
        env_pts = np.load(s_g_file, allow_pickle=True)
        print("Load start goal suc!")
        # print("s_g shape:",env_pts.shape)
    # planning
    paths_all = []
    suc_cnt = 0
    for i in range(5):
        # print("Planning Env:", i)
        paths_env = []
        rec_env = rec_envs[i, :, :]
        pl.env_rob.load_rec_obs(rec_env)
        for j in range(5):
            print("Planning Env Path:", i, j)
            vis_i_j = vis + "_env_" + str(i) + "_pts_" + str(j)
            start = env_pts[i][j][0]
            goal = env_pts[i][j][1]
            start = pl.pl_ompl.conver_list_config_to_ompl_config(start)
            goal = pl.pl_ompl.conver_list_config_to_ompl_config(goal)
            
            # solved, path = pl.plan(start=start, goal=goal, vis=None, time_lim=0.1, simple=False)
            solved, path = pl.plan(start=start, goal=goal, vis="./myfig/env_"+str(i)+"_path_"+str(j), time_lim=0.2, simple=False)
            if solved and solved.asString() == "Exact solution":
                suc_cnt += 1
                paths_env.append(path)
            print("env",i,"path",j,"Done!")
        paths_all.append(paths_env)
    np.save(path_save_file, np.array(paths_all, dtype="object"))
    print("suc_cnt:", suc_cnt)