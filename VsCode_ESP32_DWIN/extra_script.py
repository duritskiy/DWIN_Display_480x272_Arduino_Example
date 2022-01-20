Import("env")

def before_upload(source, target, env):
    print ("before_upload")
    # do some actions

env.Execute("devcon FindAll =Ports")
#env.Execute("taskkill /IM winpty-agent.exe /T /f")
#env.Execute("taskkill /IM python.exe /T /f")
# env.Execute("devcon disable \"@USB\\VID_10C4&PID_EA60\\0001\"") 
# env.Execute("devcon enable  \"@USB\\VID_10C4&PID_EA60\\0001\"")

env.Execute("disableComPort.bat")
env.Execute("enableComPort.bat")


#print(env['PROJECT_DIR'])
#env.Execute("test.bat "+env['PROJECT_DIR'])



env.AddPreAction("upload", before_upload)


def after_upload(source, target, env):
    print ("after_upload")
    # do some actions


env.AddPostAction("upload", after_upload)