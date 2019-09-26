using HW8.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace HW8.Controllers
{
    public class SubjectController : BaseController
    {
        public ActionResult All()
        {
            List<Subject> subjects = Ctx.Subjects.ToList();
            ViewBag.Blekeke = "tralala";
            return View(subjects);
        }

        [HttpGet]
        public ActionResult AddSubject()
        {
            return View();
        }

        [HttpPost]
        public ActionResult AddSubject(Subject sub)
        {
            Ctx.Subjects.Add(sub);
            Ctx.SaveChanges();
            return RedirectToAction("All");
        }

        [HttpGet]
        public ActionResult Detail(int id)
        {
            Subject s = Ctx.Subjects.FirstOrDefault(p => p.Id == id);
            if (s != null)
            {
                return View(s);
            }
            else
            {
                return new HttpNotFoundResult("Subject not found");
            }
        }

        [HttpGet]
        public ActionResult Edit(int id)
        {
            Subject s = Ctx.Subjects.FirstOrDefault(p => p.Id == id);
            if (s != null)
            {
                return View(s);
            }
            else
            {
                return new HttpNotFoundResult("Student not found");
            }
        }

        [HttpPost]
        public ActionResult Edit(Subject subj)
        {
            Subject s = Ctx.Subjects.FirstOrDefault(p => p.Id == subj.Id);
            if (s != null)
            {
                s.Abbrev = subj.Abbrev;
                s.Department = subj.Department;
                s.Name = subj.Name;
                Ctx.SaveChanges();
                return RedirectToAction("All");
            }
            else
            {
                return new HttpNotFoundResult("Student not found");
            }
        }

        [HttpGet]
        public ActionResult Delete(Subject sub)
        {
            Subject s = Ctx.Subjects.FirstOrDefault(p => p.Id == sub.Id);
            if (s != null)
            {
                Ctx.Subjects.Remove(s);
                Ctx.SaveChanges();
                return RedirectToAction("All");
            }
            else
            {
                return new HttpNotFoundResult("Student not found");
            }
        }
    }
}