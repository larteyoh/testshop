#include "config.hpp"

lua_State * neroshop::lua_state(luaL_newstate());

bool neroshop::load_config() {
        std::string user = neroshop::device::get_user();
        // "/home/<user>/.config/neroshop"
        #if defined(NEROSHOP_USE_QT)
        std::string neroshop_config_path = NEROSHOP_DEFAULT_CONFIGURATION_PATH.toStdString();
        #else
        std::string neroshop_config_path = NEROSHOP_DEFAULT_CONFIGURATION_PATH;
        #endif
        // "/home/<user>/.config/neroshop/settings.lua"
        std::string neroshop_config_name = neroshop_config_path + "/" + NEROSHOP_CONFIGURATION_FILE;
        Script script;
        if(!script.load(lua_state, neroshop_config_name)) {
            return false;
        }
        neroshop::print("\033[1;94mloaded script \"" + script.get_file() + "\"");
        return true;
	}

bool neroshop::create_config() {
    std::string user = neroshop::device::get_user();
    std::string text = "-- settings.lua\n"
        "localhost = \"127.0.0.1\";\n"
        "neroshop = {};\n"
        "neroshop[\"currency\"] = \"usd\";\n"//\n"
        "neroshop[\"window\"] = {};\n"
        //"--neroshop[\"window\"][\"x\"] = 200;\n"
        //"--neroshop[\"window\"][\"y\"] = 200;\n"
        "neroshop[\"window\"][\"width\"] = 1280;\n"
        "neroshop[\"window\"][\"height\"] = 720;\n"
        "neroshop[\"window\"][\"mode\"] = 0; --0 (window_mode) or 1 (fullscreen)\n"//\n"
        "\n"
        "neroshop[\"monero\"] = {};\n"
        "\n"
        "neroshop[\"monero\"][\"daemon\"] = {};\n" // maybe change name from daemon to node or nah?
        "neroshop[\"monero\"][\"daemon\"][\"network_type\"] = \"stagenet\"; --\"mainnet\", \"stagenet\", or \"testnet\"\n"
        "neroshop[\"monero\"][\"daemon\"][\"ip\"] = localhost; -- set to \"0.0.0.0\" to allow other wallets to connect to your node\n"
        "neroshop[\"monero\"][\"daemon\"][\"port\"] = \"38081\"; --\"18081\" (mainnet), \"38081\" (stagenet), or 28081 (testnet)\n"
        "neroshop[\"monero\"][\"daemon\"][\"confirm_external_bind\"] = false; -- if true then it confirms that you want to allow connections from other wallets outside of this system, but only when ip is set to \"0.0.0.0\"\n"
        "neroshop[\"monero\"][\"daemon\"][\"restricted_rpc\"] = true;\n"
        "neroshop[\"monero\"][\"daemon\"][\"data_dir\"] = \"/home/<user>/.bitmonero\";\n"
        "neroshop[\"monero\"][\"daemon\"][\"remote\"] = false; -- set to true if the node that you want to connect to is a remote node\n"//\n"
        "\n"
        "neroshop[\"monero\"][\"wallet\"] = {};\n"
        "neroshop[\"monero\"][\"wallet\"][\"file\"] = \"\"; -- include \".keys\" extension\n" // path or file
        "neroshop[\"monero\"][\"wallet\"][\"restore_height\"] = \"2014-04-18\"; -- block height or date (YYYY-MM-DD)\n"
        "\n"
        "neroshop[\"monero\"][\"nodes\"] = {}\n"
        "neroshop[\"monero\"][\"nodes\"][\"mainnet\"] = {\n"
        "    \"node.community.rino.io:18081\",\n"
        "    \"node.sethforprivacy.com:18089\",\n"
        "    \"node2.sethforprivacy.com:18089\",\n"
        "    \"selsta1.featherwallet.net:18081\",\n"
        "    \"selsta2.featherwallet.net:18081\",\n"
        "    \"node.monerooutreach.org:18081\",\n"
        "    \"node.majesticbank.is:18089\",\n"
        "    \"node.majesticbank.su:18089\",\n"
        "    \"xmr-node-eu.cakewallet.com:18081\",\n"
        "    \"xmr-node-usa-east.cakewallet.com:18081\",\n"
        "    \"canada.node.xmr.pm:18089\",\n"
        "    \"singapore.node.xmr.pm:18089\",\n"
        "    \"nodes.hashvault.pro:18081\",\n"
        "    \"node.supportxmr.com:18081\",\n"
        "    \"node.xmr.ru:18081\"\n"
        "};\n"
        "neroshop[\"monero\"][\"nodes\"][\"stagenet\"] = {\n"
        "    \"super.fast.node.xmr.pm:38089\",\n"
        "    \"stagenet.community.rino.io:38081\"\n"
        "};\n" 
        "neroshop[\"monero\"][\"nodes\"][\"testnet\"] = {\n" 
        "    \"testnet.community.rino.io:28081\"\n"
        "};\n";
        // swap data_dir with user
    #if defined(__gnu_linux__) // works!    
        text = neroshop::string::swap_first_of(text, "/home/<user>/.bitmonero", ("/home/" + user + "/.bitmonero"));
    #endif    
        // "/home/<user>/.config/neroshop"
        #if defined(NEROSHOP_USE_QT)
        std::string neroshop_config_path = NEROSHOP_DEFAULT_CONFIGURATION_PATH.toStdString();
        #else        
        std::string neroshop_config_path = NEROSHOP_DEFAULT_CONFIGURATION_PATH;//"/home/" + user + "/.config/neroshop"; // neroshop::device::get_user()
        #endif
        // "/home/<user>/.config/neroshop/config.lua"
        std::string neroshop_config_name = neroshop_config_path + "/" + NEROSHOP_CONFIGURATION_FILE;
        // if file already exists, no need to create it again
        if(std::filesystem::is_regular_file(neroshop_config_name)) return false; // false because it will not be created // if true then it will cause "PANIC: unprotected error in call to Lua API (attempt to index a nil value)" error
        // check if script works before saving
        if(luaL_dostring(lua_state, text.c_str()) != 0) {
		    neroshop::print(LUA_TAG "\033[0;91minvalid Lua code");
		    lua_error(lua_state);
		    return false; // exit function so it does not save text
	    }
        // if path does not exist
        if(!std::filesystem::is_directory(neroshop_config_path)) 
        {   // create the path
            neroshop::print("directory \"" + neroshop_config_path + "\" does not exist, but I will create it for you (^_^)", 2);
            if(!std::filesystem::create_directories(neroshop_config_path)) { neroshop::print("create_config error: failed to make the path. Sorry (ᵕ人ᵕ)! ...", 1); return false; }
            neroshop::print("\033[1;97;49mcreated path \"" + neroshop_config_path + "\"");
        }
        // if path exists, but the file is missing or deleted
        if(!std::filesystem::is_regular_file(neroshop_config_name)) {
            // create config file (one time)
            std::ofstream cfg;
            cfg.open (neroshop_config_name, std::ios::out | std::ios::trunc);
            cfg << text << "\n"; // write to file
            cfg.close();
            neroshop::print("\033[1;97;49mcreated file \"" + neroshop_config_name + "\"\033[0m");  
        }
        return true;		
	}
	//////////////////////////////
	//void neroshop::edit_config(const std::string& old_str, const std::string& new_str); // not possible to edit lua files with my current knowledge

extern bool neroshop::open_config() {
    if(!neroshop::create_config()) { 
        if(!neroshop::load_config()) {
            neroshop::print("Failed to load configuration file", 1);
            return false;
        }
    }
    return true;
}

bool neroshop::create_configuration_file() {
    return neroshop::create_config();
}

bool neroshop::load_configuration_file() {
    return neroshop::load_config();
}

bool neroshop::open_configuration_file() {
    return neroshop::open_config();
}

lua_State * neroshop::get_lua_state() {
	return lua_state;
}
