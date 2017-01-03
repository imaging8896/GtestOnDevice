from os.path import dirname
from os.path import abspath

from utils.dockerBuildUtils import dockerBuildUtils

if __name__ == '__main__':
    this_dir = abspath(dirname(__file__))
    dockerBuildUtils.make_ndk_build(this_dir)
