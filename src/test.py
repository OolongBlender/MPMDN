import numpy as np


if __name__ == '__main__':
    # saved_path = np.load("./Data/S2D_Rigidbody_Path_.npy", allow_pickle=True)
    # print(saved_path.shape)
    # print(saved_path)

    path_save_file = "./Data/S2D_Rigidbody_Path_"
    s_g_file = "./Data/S2D/S2D_RB_sg_ev_not_trivial.npy"
    env_file = "./Data/S2D/S2D_env_100_rec.npy"

    # load env
    rec_envs = np.load(env_file, allow_pickle=True)
    print("envs shape:", rec_envs.shape)
    env_pts = np.load(s_g_file, allow_pickle=True)
    print("s_g shape:",env_pts.shape)
    for i in range (1,2):
        print(i)     

