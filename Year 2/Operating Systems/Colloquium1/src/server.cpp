#include <httplib.h>
#include <nlohmann/json.hpp>
#include <factorial.h>
#include <unique.h>
#include <linked_list.h>
#include <iostream>
#include <vector>

using json = nlohmann::json;
using namespace httplib;

int main()
{
    Server svr;

    svr.Get("/health", [](const Request& req, Response& res)
        { res.set_content(R"({"status":"ok"})", "application/json"); });

    svr.Get("/factorial", [](const Request& req, Response& res)
        {
        if (!req.has_param("n"))
        {
            res.status = 400;
            res.set_content(R"({"error":"missing parameter n"})", "application/json");
            return;
        }
        try
        {
            int n = std::stoi(req.get_param_value("n"));
            auto v = generateFactorials(n);
            json out = { {"result", v} };
            res.set_content(out.dump(), "application/json");
        }
        catch (std::exception& e)
        {
            json out = { {"error", e.what()} };
            res.status = 400;
            res.set_content(out.dump(), "application/json");
        }
        });

    svr.Post("/unique", [](const Request& req, Response& res)
        {
        try
        {
            auto j = json::parse(req.body);
            auto arr = j.at("values").get<std::vector<int>>();
            auto u = removeDuplicates(arr);
            json out = { {"result", u} };
            res.set_content(out.dump(), "application/json");
        }
        catch (std::exception& e)
        {
            json out = { {"error", e.what()} };
            res.status = 400;
            res.set_content(out.dump(), "application/json");
        }
        });

    svr.Post("/reverse", [](const Request& req, Response& res)
        {
        try
        {
            auto j = json::parse(req.body);
            auto arr = j.at("values").get<std::vector<int>>();
            if (arr.empty())
            {
                json out = { {"result", std::vector<int>{}} };
                res.set_content(out.dump(), "application/json");
                return;
            }
            auto head = std::make_shared<Node>(arr[0]);
            auto cur = head;
            for (size_t i = 1; i < arr.size(); ++i) { cur->next = std::make_shared<Node>(arr[i]); cur = cur->next; }
            auto rev = reverseList(head);
            std::vector<int> outv;
            for (auto p = rev; p; p = p->next) outv.push_back(p->value);
            json out = { {"result", outv} };
            res.set_content(out.dump(), "application/json");
        }
        catch (std::exception& e)
        {
            json out = { {"error", e.what()} };
            res.status = 400;
            res.set_content(out.dump(), "application/json");
        }
        });

    std::cout << "Server listening on http://localhost:8080\n";
    svr.listen("0.0.0.0", 8080);
    return 0;
}